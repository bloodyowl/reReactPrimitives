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

let component = ReasonReact.statefulComponent "TouchableOpacity";

let make
    ::onPress
    ::style=?
    ::onKeyPress=?
    ::onKeyDown=?
    ::onKeyUp=?
    ::onFocus=?
    ::onBlur=?
    children => {
  let handleFocus event {ReasonReact.state: state} => {
    switch onFocus {
    | Some onFocus => onFocus event
    | None => ()
    };
    switch state.focus {
    | FocusedFromMouse => ReasonReact.NoUpdate
    | _ => ReasonReact.Update {...state, focus: FocusedFromKeyboard}
    }
  };
  let handleBlur event {ReasonReact.state: state} => {
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
    render: fun ({state} as self) => {
      let opacityStyle =
        ReactDOMRe.Style.make
          transition::"100ms linear opacity"
          transform::"translateZ(0)"
          cursor::"pointer"
          opacity::(
            switch state.pressed {
            | Depressed => "0.5"
            | Idle => "1"
            }
          )
          ();
      <div
        role="button"
        tabIndex=0
        style=(
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
                  | None => opacityStyle
                  | Some style => ReactDOMRe.Style.combine opacityStyle style
                  }
                )
            )
            "WebkitTapHighlightColor"
            "rgba(0, 0, 0, 0)"
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
        children.(0)
      </div>
    }
  }
};
