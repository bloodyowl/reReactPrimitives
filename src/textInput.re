type state = {
  height: option int,
  inputRef: option Dom.element
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
    ::placeholder=""
    ::rows=1
    _children => {
  let setInputRef inputRef state _self =>
    ReasonReact.SilentUpdate (
      switch (Js.Null.to_opt inputRef) {
      | Some inputRef => {...state, inputRef: Some inputRef}
      | None => state
      }
    );
  let measureAndSetHeight _ state _self =>
    switch state.inputRef {
    | Some element =>
      CssStyleDeclarationRe.setProperty "height" "0" "" (getStyle element);
      let height = DomRe.Element.scrollHeight element;
      CssStyleDeclarationRe.setProperty
        "height" (string_of_int height ^ "px") "" (getStyle element);
      ReasonReact.Update {...state, height: Some height}
    | None => ReasonReact.NoUpdate
    };
  let handleChange _event state self =>
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
  {
    ...component,
    initialState: fun () => {height: None, inputRef: None},
    render: fun state self => {
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
              switch style {
              | Some style => ReactDOMRe.Style.combine style sizingStyle
              | None => sizingStyle
              }
            )
            onChange::(self.update handleChange)
            ::?onKeyDown
            ::value
            ::placeholder
            autoFocus::(Js.Boolean.to_js_boolean autoFocus)
            ()
        )
        [||]
    }
  }
};
