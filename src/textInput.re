type state = {
  height: option(int),
  inputRef: ref(option(Dom.element)),
  focused: bool
};

type action =
  | Change(string)
  | Focus
  | Blur
  | SetHeight(int);

let component = ReasonReact.reducerComponent("TextInput");

[@bs.get] external getStyle : DomRe.Element.t => Dom.cssStyleDeclaration = "style";

let setInputRef = (inputRef, {ReasonReact.state}) =>
  state.inputRef := Js.Nullable.to_opt(inputRef);

/* TODO: manage types and local validation */
let make =
    (
      ~multiline=false,
      ~autoSize=false,
      ~autoFocus=false,
      ~disabled=false,
      ~_type="text",
      ~id=?,
      ~name=?,
      ~value,
      ~style=?,
      ~onTextChange,
      ~onKeyDown=?,
      ~onPaste=?,
      ~onFocus=?,
      ~onBlur=?,
      ~focusedStyle=?,
      ~placeholder="",
      ~rows=1,
      _children
    ) => {
  let measureAndSetHeight = ((), {ReasonReact.state, ReasonReact.send}) =>
    switch state.inputRef {
    | {contents: Some(element)} =>
      CssStyleDeclarationRe.setProperty("height", "0", "", getStyle(element));
      let height = DomRe.Element.scrollHeight(element);
      CssStyleDeclarationRe.setProperty(
        "height",
        string_of_int(height) ++ "px",
        "",
        getStyle(element)
      );
      send(SetHeight(height))
    | _ => ()
    };
  let handleResize = ({ReasonReact.handle}) =>
    if (multiline && autoSize) {
      Bs_webapi.requestAnimationFrame((_) => handle(measureAndSetHeight, ()))
    };
  let handleChange = (value, self) => {
    onTextChange(value);
    handleResize(self)
  };
  {
    ...component,
    initialState: () => {height: None, inputRef: ref(None), focused: false},
    didMount: (self) => {
      handleResize(self);
      ReasonReact.NoUpdate
    },
    reducer: (action, state) =>
      switch action {
      | Focus => ReasonReact.Update({...state, focused: true})
      | Blur => ReasonReact.Update({...state, focused: false})
      | Change(value) => ReasonReact.SideEffects(handleChange(value))
      | SetHeight(height) => ReasonReact.Update({...state, height: Some(height)})
      },
    render: ({send, state, handle}) => {
      let sizingStyle =
        ReactDOMRe.Style.make(
          ~resize="none",
          ~boxSizing="content-box",
          ~fontSize="16px",
          ~height=
            switch state.height {
            | None => "auto"
            | Some(height) => string_of_int(height) ++ "px"
            },
          ()
        );
      ReactDOMRe.createElement(
        multiline ? "textarea" : "input",
        ~props=
          ReactDOMRe.props(
            ~ref=handle(setInputRef),
            ~rows,
            ~_type,
            ~id?,
            ~name?,
            ~disabled=Js.Boolean.to_js_boolean(disabled),
            ~style=
              ReactDOMRe.Style.combine(
                switch style {
                | Some(style) => ReactDOMRe.Style.combine(style, sizingStyle)
                | None => sizingStyle
                },
                switch focusedStyle {
                | Some(style) when state.focused == true => style
                | _ => ReactDOMRe.Style.make()
                }
              ),
            ~onChange=
              (event) =>
                send(Change(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value)),
            ~onKeyDown?,
            ~onPaste?,
            ~onFocus=
              (event) => {
                switch onFocus {
                | Some(onFocus) => onFocus(event)
                | None => ()
                };
                send(Focus)
              },
            ~onBlur=
              (event) => {
                switch onBlur {
                | Some(onBlur) => onBlur(event)
                | None => ()
                };
                send(Blur)
              },
            ~value,
            ~placeholder,
            ~autoFocus=Js.Boolean.to_js_boolean(autoFocus),
            ()
          ),
        [||]
      )
    }
  }
};
