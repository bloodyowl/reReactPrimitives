type state = {isReady: bool};

type action =
  | Init;

let component = ReasonReact.reducerComponent("Image");

type resizeMode =
  | Cover
  | Contain
  | Actual;

let make =
    (
      ~source,
      ~resizeMode,
      ~width,
      ~height,
      ~backgroundColor,
      ~round=false,
      ~alternativeText=?,
      _children,
    ) => {
  ...component,
  initialState: (_) => {isReady: false},
  reducer: (action, _state) =>
    switch (action) {
    | Init => ReasonReact.Update({isReady: true})
    },
  didMount: ({send}) => send(Init),
  render: ({state}) =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~width=string_of_int(width) ++ "px",
          ~height=string_of_int(height) ++ "px",
          ~backgroundSize=
            switch (resizeMode) {
            | Cover => "cover"
            | Actual => "auto"
            | Contain => "contain"
            },
          ~backgroundRepeat="no-repeat",
          ~backgroundPosition="50% 50%",
          ~backgroundColor,
          ~backgroundImage=state.isReady ? "url(" ++ source ++ ")" : "",
          ~borderRadius=
            round ? string_of_int(min(width, height)) ++ "px" : "0px",
          (),
        )
      )>
      (
        switch (alternativeText) {
        | Some(text) => <ScreenReaderContent text />
        | None => ReasonReact.null
        }
      )
    </div>,
};
