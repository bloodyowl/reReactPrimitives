type mode =
  | Horizontal
  | Vertical;

type state = {openTab: int};

type action =
  | SetActiveTab(int);

let component = ReasonReact.reducerComponent("TabbedView");

let make =
    (
      ~initiallyOpenTab=0,
      ~mode=Vertical,
      ~tabs,
      ~color="#4A90E2",
      ~tabHeadingPadding="15px 20px",
      _children,
    ) => {
  ...component,
  initialState: () => {openTab: initiallyOpenTab},
  reducer: (action, _) =>
    switch (action) {
    | SetActiveTab(openTab) => ReasonReact.Update({openTab: openTab})
    },
  render: ({state, send}) =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~display="flex",
          ~flexGrow="1",
          ~flexDirection=
            switch (mode) {
            | Horizontal => "row"
            | Vertical => "column"
            },
          (),
        )
      )>
      <div
        style=(
          ReactDOMRe.Style.make(
            ~position="relative",
            ~display="flex",
            ~flexGrow="0",
            ~flexShrink="0",
            (),
          )
        )>
        <div
          style=(
            ReactDOMRe.Style.make(
              ~display="flex",
              ~flexGrow="1",
              ~flexDirection=
                switch (mode) {
                | Horizontal => "column"
                | Vertical => "row"
                },
              ~justifyContent=
                switch (mode) {
                | Horizontal => ""
                | Vertical => "center"
                },
              ~boxShadow=
                switch (mode) {
                | Vertical => "0 1px rgba(0, 0, 0, 0.1)"
                | Horizontal => "1px 0 rgba(0, 0, 0, 0.1)"
                },
              (),
            )
          )>
          (
            tabs
            |> Array.mapi((index, (tabTitle, _)) =>
                 <TouchableOpacity
                   key=(string_of_int(index))
                   style=(
                     ReactDOMRe.Style.make(
                       ~color=
                         index === state.openTab ?
                           color : "rgba(0, 0, 0, 0.6)",
                       ~boxShadow=
                         index === state.openTab ?
                           switch (mode) {
                           | Horizontal => "3px 0 " ++ color
                           | Vertical => "0 3px " ++ color
                           } :
                           "none",
                       ~padding=tabHeadingPadding,
                       (),
                     )
                   )
                   onPress=(_ => send(SetActiveTab(index)))>
                   tabTitle
                 </TouchableOpacity>
               )
            |> ReasonReact.array
          )
        </div>
      </div>
      <div
        style=(
          ReactDOMRe.Style.make(
            ~flexGrow="1",
            ~display="flex",
            ~flexDirection="column",
            (),
          )
        )>
        {
          let (_activeTab, renderActiveTab) = tabs[state.openTab];
          renderActiveTab();
        }
      </div>
    </div>,
};
