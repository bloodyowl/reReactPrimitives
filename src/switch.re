type focus =
  | NotFocused
  | FocusedFromMouse
  | FocusedFromKeyboard;

type status =
  | Idle
  | Updating;

type value = (status, bool);

type action =
  | Focus
  | Blur
  | MouseDown
  | KeyPress((int, int));

let component = ReasonReact.reducerComponent("Switch");

let make = (~value, ~onValueChange, ~disabled=false, _children) => {
  let handleChange = () => {
    let (_state, value) = value;
    onValueChange(! value);
  };
  {
    ...component,
    initialState: () => NotFocused,
    reducer: (action, state) =>
      switch (action) {
      | Focus =>
        switch (state) {
        | FocusedFromMouse => ReasonReact.NoUpdate
        | _ => ReasonReact.Update(FocusedFromKeyboard)
        }
      | Blur => ReasonReact.Update(NotFocused)
      | MouseDown => ReasonReact.Update(FocusedFromMouse)
      | KeyPress(keys) =>
        switch (keys) {
        | (13, _)
        | (_, 13)
        | (32, _)
        | (_, 32) => ReasonReact.SideEffects(((_) => handleChange()))
        | _ => ReasonReact.NoUpdate
        }
      },
    render: ({state, send}) =>
      ReasonReact.cloneElement(
        <div
          role="checkbox"
          tabIndex=0
          onMouseDown=((_) => send(MouseDown))
          onKeyPress=(
            event =>
              if (! disabled) {
                send(
                  KeyPress((
                    ReactEvent.Keyboard.keyCode(event),
                    ReactEvent.Keyboard.charCode(event),
                  )),
                );
              }
          )
          onFocus=((_) => send(Focus))
          onBlur=((_) => send(Blur))
          onClick=(
            (_) =>
              if (! disabled) {
                handleChange();
              }
          )
          style=(
            ReactDOMRe.Style.unsafeAddProp(
              ReactDOMRe.Style.make(
                ~width="35px",
                ~height="14px",
                ~borderRadius="7px",
                ~boxShadow="inset 0 0 0 1px rgba(0, 0, 0, 0.1)",
                ~position="relative",
                ~cursor=disabled ? "default" : "pointer",
                ~backgroundColor=
                  switch (value) {
                  | (Idle, true) => "rgba(74, 144, 226, 1)"
                  | (Idle, false) => "rgba(0, 0, 0, 0.2)"
                  | (Updating, true) => "rgba(74, 144, 226, 0.5)"
                  | (Updating, false) => "rgba(0, 0, 0, 0.1)"
                  },
                ~opacity=disabled ? ".4" : "1",
                ~outline=
                  switch (state) {
                  | FocusedFromMouse => "none"
                  | _ => ""
                  },
                (),
              ),
              "WebkitTapHighlightColor",
              "rgba(0, 0, 0, 0)",
            )
          )>
          <div
            style=(
              ReactDOMRe.Style.make(
                ~width="20px",
                ~height="20px",
                ~backgroundColor="#fff",
                ~boxShadow=
                  "0 0 0 1px rgba(0, 0, 0, 0.1), 0 2px 4px rgba(0, 0, 0, 0.1)",
                ~position="absolute",
                ~borderRadius="10px",
                ~top="-3px",
                ~transition="200ms left ease-in-out",
                ~display="flex",
                ~flexDirection="row",
                ~alignItems="center",
                ~justifyContent="center",
                ~left=
                  switch (value) {
                  | (_, true) => "20px"
                  | (_, false) => "-5px"
                  },
                (),
              )
            )>
            (
              switch (value) {
              | (Idle, _) => ReasonReact.null
              | (Updating, _) =>
                <ActivityIndicator size=14.0 color=(200, 200, 200) />
              }
            )
          </div>
        </div>,
        ~props={
          "aria-checked":
            switch (value) {
            | (Idle, true) => "true"
            | (Idle, false) => "false"
            | (Updating, true) => "mixed"
            | (Updating, false) => "mixed"
            },
        },
        [||],
      ),
  };
};
