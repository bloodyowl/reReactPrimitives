type state = {
  height: option int,
  inputRef: option Dom.element,
  focused: bool
};

let component = ReasonReact.statefulComponent "TextInput";

external getStyle : DomRe.Element.t => Dom.cssStyleDeclaration = "style" [@@bs.get];

/* TODO: manage types and local validation */
let make
    ::multiline=false
    ::autoSize=false
    ::autoFocus=false
    ::value
    ::style=?
    ::onTextChange
    ::onKeyDown=?
    ::onPaste=?
    ::onFocus=?
    ::onBlur=?
    ::focusedStyle=?
    ::placeholder=""
    ::rows=1
    _children => {
  let setInputRef inputRef {ReasonReact.state: state} =>
    ReasonReact.SilentUpdate (
      switch (Js.Null.to_opt inputRef) {
      | Some inputRef => {...state, inputRef: Some inputRef}
      | None => state
      }
    );
  let measureAndSetHeight _ {ReasonReact.state: state} =>
    switch state.inputRef {
    | Some element =>
      CssStyleDeclarationRe.setProperty "height" "0" "" (getStyle element);
      let height = DomRe.Element.scrollHeight element;
      CssStyleDeclarationRe.setProperty
        "height" (string_of_int height ^ "px") "" (getStyle element);
      ReasonReact.Update {...state, height: Some height}
    | None => ReasonReact.NoUpdate
    };
  let handleChange _event ({ReasonReact.state: state} as self) =>
    switch state.inputRef {
    | Some element =>
      let value = (ReactDOMRe.domElementToObj element)##value;
      onTextChange value;
      /* don't bother trigger a measurement if using an input */
      if (multiline && autoSize) {
        Bs_webapi.requestAnimationFrame (self.ReasonReact.update measureAndSetHeight)
      };
      ReasonReact.NoUpdate
    | None => ReasonReact.NoUpdate
    };
  let handleFocus event {ReasonReact.state: state} => {
    switch onFocus {
    | Some onFocus => onFocus event
    | None => ()
    };
    ReasonReact.Update {...state, focused: true}
  };
  let handleBlur event {ReasonReact.state: state} => {
    switch onBlur {
    | Some onBlur => onBlur event
    | None => ()
    };
    ReasonReact.Update {...state, focused: false}
  };
  {
    ...component,
    initialState: fun () => {height: None, inputRef: None, focused: false},
    render: fun ({state} as self) => {
      let sizingStyle =
        ReactDOMRe.Style.make
          resize::"none"
          boxSizing::"content-box"
          fontSize::"16px"
          height::(
            switch state.height {
            | None => "auto"
            | Some height => string_of_int height ^ "px"
            }
          )
          ();
      ReactDOMRe.createElement
        (multiline ? "textarea" : "input")
        props::(
          ReactDOMRe.props
            ref::(self.update setInputRef)
            ::rows
            style::(
              ReactDOMRe.Style.combine
                (
                  switch style {
                  | Some style => ReactDOMRe.Style.combine style sizingStyle
                  | None => sizingStyle
                  }
                )
                (
                  switch focusedStyle {
                  | Some style when self.state.focused == true => style
                  | _ => ReactDOMRe.Style.make ()
                  }
                )
            )
            onChange::(self.update handleChange)
            ::?onKeyDown
            ::?onPaste
            onFocus::(self.update handleFocus)
            onBlur::(self.update handleBlur)
            ::value
            ::placeholder
            autoFocus::(Js.Boolean.to_js_boolean autoFocus)
            ()
        )
        [||]
    }
  }
};
