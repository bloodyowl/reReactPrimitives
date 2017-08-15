type focus =
  | NotFocused
  | FocusedFromMouse
  | FocusedFromKeyboard;

type state = {
  layer: option LayerManager.layer,
  focus
};

let component = ReasonReact.statefulComponent "Picker";

module PickerLayerManager = LayerManager.Make LayerManager.DefaultImpl;

external focus : unit = "" [@@bs.send.pipe : DomRe.Element.t];

let make ::options ::renderPicker ::renderOption ::value ::onValueChange ::padding="10px" _children => {
  let handleFocus _event {ReasonReact.state: state} =>
    switch state.focus {
    | FocusedFromMouse => ReasonReact.NoUpdate
    | _ => ReasonReact.Update {...state, focus: FocusedFromKeyboard}
    };
  let handleBlur _event {ReasonReact.state: state} =>
    ReasonReact.Update {...state, focus: NotFocused};
  let handleMouseDown _event {ReasonReact.state: state} =>
    ReasonReact.Update {...state, focus: FocusedFromMouse};
  let hideOptions _ {ReasonReact.state: state} =>
    switch state.layer {
    | Some layer =>
      PickerLayerManager.remove layer;
      ReasonReact.SilentUpdate {...state, layer: None}
    | None => ReasonReact.NoUpdate
    };
  let moveFocus event {ReasonReact.state: state} =>
    switch (ReactEventRe.Keyboard.keyCode event) {
    | 38 =>
      switch (ReactEventRe.Keyboard.target event |> DomRe.Element.previousElementSibling) {
      | Some element =>
        focus element;
        ReasonReact.Update {...state, focus: FocusedFromKeyboard}
      | None =>
        switch (ReactEventRe.Keyboard.target event |> DomRe.Element.parentElement) {
        | Some element =>
          switch (element |> DomRe.Element.lastElementChild) {
          | Some element =>
            focus element;
            ReasonReact.Update {...state, focus: FocusedFromKeyboard}
          | None => ReasonReact.NoUpdate
          }
        | None => ReasonReact.NoUpdate
        }
      }
    | 40 =>
      switch (ReactEventRe.Keyboard.target event |> DomRe.Element.nextElementSibling) {
      | Some element =>
        focus element;
        ReasonReact.Update {...state, focus: FocusedFromKeyboard}
      | None =>
        switch (ReactEventRe.Keyboard.target event |> DomRe.Element.parentElement) {
        | Some element =>
          switch (element |> DomRe.Element.firstElementChild) {
          | Some element =>
            focus element;
            ReasonReact.Update {...state, focus: FocusedFromKeyboard}
          | None => ReasonReact.NoUpdate
          }
        | None => ReasonReact.NoUpdate
        }
      }
    | _ => ReasonReact.NoUpdate
    };
  let renderOptionWithEvent self index item =>
    <TouchableHighlight
      key=(string_of_int index)
      ref=(
        index == 0 ?
          fun item =>
            switch (Js.Null.to_opt item) {
            | Some item => focus (ReactDOMRe.findDOMNode item)
            | None => ()
            } :
          (fun _ => ())
      )
      onPress=(
        fun _ => {
          onValueChange (Some item);
          self.ReasonReact.update hideOptions ()
        }
      )
      onKeyUp=(self.update moveFocus)
      onBlur=(self.update handleBlur)
      style=(
        ReactDOMRe.Style.make
          cursor::"pointer"
          outline::(
            switch self.state.focus {
            | FocusedFromMouse => "none"
            | _ => ""
            }
          )
          ()
      )
      focusedFromKeyboardStyle=(
        ReactDOMRe.Style.make
          backgroundImage::"linear-gradient(to bottom, rgba(0, 0, 0, 0.05), rgba(0, 0, 0, 0.05))"
          opacity::"0.8"
          outline::"none"
          ()
      )
      underlayColor="rgba(0, 0, 0, 0.05)">
      (renderOption item value)
    </TouchableHighlight>;
  let whenLayerReady layer self => {
    PickerLayerManager.render
      layer
      <div>
        <div
          onClick=(fun _ => self.ReasonReact.update hideOptions ())
          style=(
            ReactDOMRe.Style.make position::"fixed" top::"0" left::"0" right::"0" bottom::"0" ()
          )
        />
        <div
          style=(
            ReactDOMRe.Style.make
              position::"relative"
              backgroundColor::"#fff"
              borderBottomLeftRadius::"3px"
              borderBottomRightRadius::"3px"
              overflow::"auto"
              zIndex::"1"
              boxShadow::"0 0 0 1px rgba(0, 0, 0, 0.1), 0 2px 4px rgba(0, 0, 0, 0.16"
              ()
          )>
          (
            options |> List.mapi (renderOptionWithEvent self) |> Array.of_list |> ReasonReact.arrayToElement
          )
        </div>
      </div>;
    ReasonReact.SilentUpdate {...self.state, layer: Some layer}
  };
  let handleKeyPress event ({ReasonReact.state: state} as self) =>
    switch (ReactEventRe.Keyboard.keyCode event, ReactEventRe.Keyboard.charCode event) {
    | (13, _)
    | (_, 13)
    | (32, _)
    | (_, 32) =>
      ReactEventRe.Keyboard.preventDefault event;
      switch state.layer {
      | Some _layer =>
        ignore (hideOptions () self);
        ReasonReact.NoUpdate
      | None =>
        let layer =
          PickerLayerManager.make (Contextualized (ReactEventRe.Keyboard.target event) Bottom);
        ignore (
          Js.Promise.then_
            (
              fun layer => {
                self.ReasonReact.update whenLayerReady layer;
                Js.Promise.resolve ()
              }
            )
            layer
        );
        ReasonReact.NoUpdate
      }
    | _ => ReasonReact.NoUpdate
    };
  let showOptions event ({ReasonReact.state: state} as self) =>
    switch state.layer {
    | Some _layer =>
      ignore (hideOptions () self);
      ReasonReact.NoUpdate
    | None =>
      let layer =
        PickerLayerManager.make (Contextualized (ReactEventRe.Mouse.target event) Bottom);
      ignore (
        Js.Promise.then_
          (
            fun layer => {
              self.ReasonReact.update whenLayerReady layer;
              Js.Promise.resolve ()
            }
          )
          layer
      );
      ReasonReact.Update {...state, focus: FocusedFromMouse}
    };
  {
    ...component,
    initialState: fun () => {focus: NotFocused, layer: None},
    render: fun self =>
      <div
        tabIndex=0
        role="button"
        style=(
          ReactDOMRe.Style.unsafeAddProp
            (
              ReactDOMRe.Style.make
                ::padding
                cursor::"pointer"
                outline::(
                  switch self.state.focus {
                  | FocusedFromMouse => "none"
                  | _ => ""
                  }
                )
                ()
            )
            "WebkitTapHighlightColor"
            "rgba(0, 0, 0, 0)"
        )
        onFocus=(self.update handleFocus)
        onBlur=(self.update handleBlur)
        onMouseDown=(self.update handleMouseDown)
        onTouchStart=(self.update handleMouseDown)
        onKeyPress=(self.update handleKeyPress)
        onClick=(self.update showOptions)>
        (renderPicker value)
      </div>
  }
};
