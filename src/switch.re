type focus =
  | NotFocused
  | FocusedFromMouse
  | FocusedFromKeyboard;

type status =
  | Idle
  | Updating;

type value = (status, bool);

let component = ReasonReact.statefulComponent "Switch";

let make ::value ::onValueChange _children => {
  let handleFocus _event {ReasonReact.state: state} =>
    switch state {
    | FocusedFromMouse => ReasonReact.NoUpdate
    | _ => ReasonReact.Update FocusedFromKeyboard
    };
  let handleBlur _event _ => ReasonReact.Update NotFocused;
  let handleMouseDown _event _ => ReasonReact.Update FocusedFromMouse;
  let handleChange _event => {
    let (_state, value) = value;
    onValueChange (not value)
  };
  let handleKeyPress event _ =>
    switch (ReactEventRe.Keyboard.keyCode event, ReactEventRe.Keyboard.charCode event) {
    | (13, _)
    | (_, 13)
    | (32, _)
    | (_, 32) =>
      let (_state, value) = value;
      onValueChange (not value);
      ReasonReact.NoUpdate
    | _ => ReasonReact.NoUpdate
    };
  {
    ...component,
    initialState: fun () => NotFocused,
    render: fun {state, update} =>
      ReasonReact.cloneElement
        <div
          role="checkbox"
          tabIndex=0
          onMouseDown=(update handleMouseDown)
          onKeyPress=(update handleKeyPress)
          onFocus=(update handleFocus)
          onBlur=(update handleBlur)
          onClick=handleChange
          style=(
            ReactDOMRe.Style.unsafeAddProp
              (
                ReactDOMRe.Style.make
                  width::"35px"
                  height::"14px"
                  borderRadius::"7px"
                  boxShadow::"inset 0 0 0 1px rgba(0, 0, 0, 0.1)"
                  position::"relative"
                  cursor::"pointer"
                  backgroundColor::(
                    switch value {
                    | (Idle, true) => "rgba(74, 144, 226, 1)"
                    | (Idle, false) => "rgba(0, 0, 0, 0.2)"
                    | (Updating, true) => "rgba(74, 144, 226, 0.5)"
                    | (Updating, false) => "rgba(0, 0, 0, 0.1)"
                    }
                  )
                  outline::(
                    switch state {
                    | FocusedFromMouse => "none"
                    | _ => ""
                    }
                  )
                  ()
              )
              "WebkitTapHighlightColor"
              "rgba(0, 0, 0, 0)"
          )>
          <div
            style=(
              ReactDOMRe.Style.make
                width::"20px"
                height::"20px"
                backgroundColor::"#fff"
                boxShadow::"0 0 0 1px rgba(0, 0, 0, 0.1), 0 2px 4px rgba(0, 0, 0, 0.1)"
                position::"absolute"
                borderRadius::"10px"
                top::"-3px"
                transition::"200ms left ease-in-out"
                display::"flex"
                flexDirection::"row"
                alignItems::"center"
                justifyContent::"center"
                left::(
                  switch value {
                  | (_, true) => "20px"
                  | (_, false) => "-5px"
                  }
                )
                ()
            )>
            (
              switch value {
              | (Idle, _) => ReasonReact.nullElement
              | (Updating, _) => <ActivityIndicator size=14.0 color=(200, 200, 200) />
              }
            )
          </div>
        </div>
        props::{
          "aria-checked":
            switch value {
            | (Idle, true) => "true"
            | (Idle, false) => "false"
            | (Updating, true) => "mixed"
            | (Updating, false) => "mixed"
            }
        }
        [||]
  }
};
