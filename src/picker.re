type focus =
  | NotFocused
  | FocusedFromMouse
  | FocusedFromKeyboard;

type state = {
  layer: option(LayerManager.layer),
  focus
};

type action =
  | Focus
  | Blur
  | MouseDown
  | KeyPress((int, int), DomRe.Element.t)
  | ShowOptions(DomRe.Element.t)
  | HideOptions
  | SetLayer(LayerManager.layer)
  | MoveFocus((int, DomRe.Element.t));

let component = ReasonReact.reducerComponent("Picker");

module PickerLayerManager = LayerManager.Make(LayerManager.DefaultImpl);

[@bs.send.pipe : DomRe.Element.t] external focus : unit = "";

let renderOptionWithEvent =
    (~renderOption, ~onValueChange, ~value, {ReasonReact.send}, index, item) =>
  <TouchableHighlight
    key=(string_of_int(index))
    ref=(
      index == 0 ?
        (item) =>
          switch (Js.Nullable.to_opt(item)) {
          | Some(item) => Webapi.requestAnimationFrame((_) => focus(ReactDOMRe.findDOMNode(item)))
          | None => ()
          } :
        ((_) => ())
    )
    onPress=(
      (_) => {
        onValueChange(Some(item));
        send(HideOptions);
      }
    )
    onKeyUp=(
      (event) =>
        send(
          MoveFocus((ReactEventRe.Keyboard.keyCode(event), ReactEventRe.Keyboard.target(event)))
        )
    )
    onBlur=((_) => send(Blur))
    style=(ReactDOMRe.Style.make(~cursor="pointer", ()))
    focusedFromKeyboardStyle=(
      ReactDOMRe.Style.make(
        ~backgroundImage="linear-gradient(to bottom, rgba(0, 0, 0, 0.05), rgba(0, 0, 0, 0.05))",
        ~opacity="0.8",
        ~outline="none",
        ()
      )
    )
    underlayColor="rgba(0, 0, 0, 0.05)">
    (renderOption(item, value))
  </TouchableHighlight>;

let makeLayer = (~target, {ReasonReact.send}) =>
  ignore(
    PickerLayerManager.make(Contextualized(target, Bottom))
    |> Js.Promise.then_(
         (layer) => {
           send(SetLayer(layer));
           Js.Promise.resolve();
         }
       )
  );

let make =
    (
      ~options,
      ~renderPicker,
      ~renderOption,
      ~value,
      ~onValueChange,
      ~padding="10px",
      ~disabled=false,
      _children
    ) => {
  let whenLayerReady = ({ReasonReact.state, ReasonReact.send} as self) =>
    switch state.layer {
    | Some(layer) =>
      PickerLayerManager.render(
        layer,
        <div>
          <div
            onClick=((_) => send(HideOptions))
            style=(
              ReactDOMRe.Style.make(
                ~position="fixed",
                ~top="0",
                ~left="0",
                ~right="0",
                ~bottom="0",
                ()
              )
            )
          />
          <div
            style=(
              ReactDOMRe.Style.make(
                ~position="relative",
                ~backgroundColor="#fff",
                ~borderBottomLeftRadius="3px",
                ~borderBottomRightRadius="3px",
                ~overflow="auto",
                ~zIndex="1",
                ~boxShadow="0 0 0 1px rgba(0, 0, 0, 0.1), 0 2px 4px rgba(0, 0, 0, 0.16",
                ()
              )
            )>
            (
              options
              |> List.mapi(renderOptionWithEvent(~renderOption, ~onValueChange, ~value, self))
              |> Array.of_list
              |> ReasonReact.arrayToElement
            )
          </div>
        </div>
      )
    | None => ()
    };
  {
    ...component,
    initialState: () => {focus: NotFocused, layer: None},
    reducer: (action, state) =>
      switch action {
      | Focus =>
        switch state.focus {
        | FocusedFromMouse => ReasonReact.NoUpdate
        | _ => ReasonReact.Update({...state, focus: FocusedFromKeyboard})
        }
      | Blur => ReasonReact.Update({...state, focus: NotFocused})
      | MouseDown => ReasonReact.Update({...state, focus: FocusedFromMouse})
      | KeyPress(keys, target) =>
        switch keys {
        | (13, _)
        | (_, 13)
        | (32, _)
        | (_, 32) => ReasonReact.SideEffects(makeLayer(~target))
        | _ => ReasonReact.NoUpdate
        }
      | ShowOptions(target) => ReasonReact.SideEffects(makeLayer(~target))
      | HideOptions =>
        switch state.layer {
        | Some(layer) =>
          ReasonReact.SilentUpdateWithSideEffects(
            {...state, layer: None},
            ((_) => PickerLayerManager.remove(layer))
          )
        | None => ReasonReact.NoUpdate
        }
      | MoveFocus((key, target)) =>
        switch key {
        | 38 =>
          switch (target |> DomRe.Element.previousElementSibling) {
          | Some(element) =>
            ReasonReact.UpdateWithSideEffects(
              {...state, focus: FocusedFromKeyboard},
              ((_) => Webapi.requestAnimationFrame((_) => focus(element)))
            )
          | None =>
            switch (target |> DomRe.Element.parentElement) {
            | Some(element) =>
              switch (element |> DomRe.Element.lastElementChild) {
              | Some(element) =>
                ReasonReact.UpdateWithSideEffects(
                  {...state, focus: FocusedFromKeyboard},
                  ((_) => Webapi.requestAnimationFrame((_) => focus(element)))
                )
              | None => ReasonReact.NoUpdate
              }
            | None => ReasonReact.NoUpdate
            }
          }
        | 40 =>
          switch (target |> DomRe.Element.nextElementSibling) {
          | Some(element) =>
            ReasonReact.UpdateWithSideEffects(
              {...state, focus: FocusedFromKeyboard},
              ((_) => Webapi.requestAnimationFrame((_) => focus(element)))
            )
          | None =>
            switch (target |> DomRe.Element.parentElement) {
            | Some(element) =>
              switch (element |> DomRe.Element.firstElementChild) {
              | Some(element) =>
                ReasonReact.UpdateWithSideEffects(
                  {...state, focus: FocusedFromKeyboard},
                  ((_) => Webapi.requestAnimationFrame((_) => focus(element)))
                )
              | None => ReasonReact.NoUpdate
              }
            | None => ReasonReact.NoUpdate
            }
          }
        | _ => ReasonReact.NoUpdate
        }
      | SetLayer(layer) =>
        ReasonReact.SilentUpdateWithSideEffects({...state, layer: Some(layer)}, whenLayerReady)
      },
    render: ({state, send}) =>
      ReasonReact.cloneElement(
        <div
          tabIndex=0
          role="button"
          style=(
            ReactDOMRe.Style.unsafeAddProp(
              ReactDOMRe.Style.make(
                ~padding,
                ~cursor=disabled ? "default" : "pointer",
                ~outline=
                  switch state.focus {
                  | FocusedFromMouse => "none"
                  | _ => ""
                  },
                ()
              ),
              "WebkitTapHighlightColor",
              "rgba(0, 0, 0, 0)"
            )
          )
          onFocus=((_) => send(Focus))
          onBlur=((_) => send(Blur))
          onMouseDown=((_) => send(MouseDown))
          onTouchStart=((_) => send(MouseDown))
          onKeyPress=(
            (event) => {
              let keys = (
                ReactEventRe.Keyboard.keyCode(event),
                ReactEventRe.Keyboard.charCode(event)
              );
              switch keys {
              | (13, _)
              | (_, 13)
              | (32, _)
              | (_, 32) => ReactEventRe.Keyboard.preventDefault(event)
              | _ => ()
              };
              send(KeyPress(keys, ReactEventRe.Keyboard.target(event)));
            }
          )
          onClick=((event) => send(ShowOptions(ReactEventRe.Mouse.target(event))))>
          (renderPicker(value))
        </div>,
        ~props={"aria-disabled": Js.Boolean.to_js_boolean(disabled)},
        [||]
      )
  };
};
