type pressed =
  | Depressed
  | Idle;

type focus =
  | NotFocused
  | FocusedFromMouse
  | FocusedFromKeyboard;

type state = {
  pressed,
  focus
};

let component = ReasonReact.statefulComponent "TouchableHighlight";

module Styles = {
  let container = ReactDOMRe.Style.make position::"relative" cursor::"pointer" ();
  let contents = ReactDOMRe.Style.make position::"relative" ();
};

let make
    ::onPress
    ::underlayColor="rgba(0, 0, 0, 0.2)"
    ::onKeyPress=?
    ::onKeyDown=?
    ::onKeyUp=?
    ::onFocus=?
    ::onBlur=?
    ::style=?
    ::focusedFromKeyboardStyle=?
    ::focusedFromMouseStyle=?
    ::disabled=false
    ::disabledStyle=?
    children => {
  let handleFocus event {ReasonReact.state: state} =>
    disabled ?
      ReasonReact.NoUpdate :
      {
        switch onFocus {
        | Some onFocus => onFocus event
        | None => ()
        };
        switch state.focus {
        | FocusedFromMouse => ReasonReact.NoUpdate
        | _ => ReasonReact.Update {...state, focus: FocusedFromKeyboard}
        }
      };
  let handleBlur event {ReasonReact.state: state} =>
    disabled ?
      ReasonReact.NoUpdate :
      {
        switch onBlur {
        | Some onBlur => onBlur event
        | None => ()
        };
        ReasonReact.Update {...state, focus: NotFocused}
      };
  let handleMouseDown _event {ReasonReact.state: _state} =>
    ReasonReact.Update {focus: FocusedFromMouse, pressed: Depressed};
  let handleMouseUp _event {ReasonReact.state: state} =>
    ReasonReact.Update {...state, pressed: Idle};
  let handleKeyDown event {ReasonReact.state: state} => {
    switch onKeyDown {
    | Some onKeyDown => onKeyDown event
    | None => ()
    };
    switch (ReactEventRe.Keyboard.keyCode event) {
    | 13
    | 32 => ReasonReact.Update {...state, pressed: Depressed}
    | _ => ReasonReact.NoUpdate
    }
  };
  let handleKeyUp event {ReasonReact.state: state} => {
    switch onKeyUp {
    | Some onKeyUp => onKeyUp event
    | None => ()
    };
    switch (ReactEventRe.Keyboard.keyCode event) {
    | 13
    | 32 => ReasonReact.Update {...state, pressed: Idle}
    | _ => ReasonReact.NoUpdate
    }
  };
  let handleKeyPress event _ => {
    switch onKeyPress {
    | Some onKeyPress => onKeyPress event
    | None => ()
    };
    switch (ReactEventRe.Keyboard.keyCode event, ReactEventRe.Keyboard.charCode event) {
    | (13, _)
    | (_, 13)
    | (32, _)
    | (_, 32) =>
      ReactEventRe.Keyboard.preventDefault event;
      onPress ();
      ReasonReact.NoUpdate
    | _ => ReasonReact.NoUpdate
    }
  };
  let handleClick _event _ => {
    onPress ();
    ReasonReact.NoUpdate
  };
  {
    ...component,
    initialState: fun _ => {pressed: Idle, focus: NotFocused},
    render: fun ({state} as self) =>
      ReasonReact.cloneElement
        <div
          role="button"
          tabIndex=0
          style=(
            ReactDOMRe.Style.combine
              (
                ReactDOMRe.Style.combine
                  (
                    ReactDOMRe.Style.unsafeAddProp
                      (
                        ReactDOMRe.Style.combine
                          (
                            ReactDOMRe.Style.make
                              outline::(
                                switch self.state.focus {
                                | FocusedFromMouse => "none"
                                | _ => ""
                                }
                              )
                              ()
                          )
                          (
                            switch style {
                            | None => Styles.container
                            | Some style => ReactDOMRe.Style.combine Styles.container style
                            }
                          )
                      )
                      "WebkitTapHighlightColor"
                      "rgba(0, 0, 0, 0)"
                  )
                  (
                    switch (self.state.focus, focusedFromKeyboardStyle, focusedFromMouseStyle) {
                    | (FocusedFromKeyboard, Some style, _) => style
                    | (FocusedFromMouse, _, Some style) => style
                    | _ => ReactDOMRe.Style.make ()
                    }
                  )
              )
              (
                switch (disabled, disabledStyle) {
                | (true, Some style) => style
                | _ => ReactDOMRe.Style.make ()
                }
              )
          )
          onFocus=(self.update handleFocus)
          onBlur=(self.update handleBlur)
          onMouseDown=(self.update handleMouseDown)
          onMouseUp=(self.update handleMouseUp)
          onTouchStart=(self.update handleMouseDown)
          onTouchEnd=(self.update handleMouseUp)
          onKeyDown=(self.update handleKeyDown)
          onKeyUp=(self.update handleKeyUp)
          onKeyPress=(self.update handleKeyPress)
          onClick=(self.update handleClick)>
          (
            switch state.pressed {
            | Depressed =>
              <div
                style=(
                  ReactDOMRe.Style.make
                    position::"absolute"
                    top::"0"
                    left::"0"
                    right::"0"
                    bottom::"0"
                    backgroundColor::underlayColor
                    ()
                )
              />
            | Idle => ReasonReact.nullElement
            }
          )
          <div style=Styles.contents> children.(0) </div>
        </div>
        props::{"aria-disabled": Js.Boolean.to_js_boolean disabled}
        [||]
  }
};
