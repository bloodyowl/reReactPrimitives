type action =
  | Scroll;

type state = {containerRef: ref(option(Dom.element))};

let component = ReasonReact.reducerComponent("ScrollView");

let setContainerRef = (containerRef, {ReasonReact.state}) =>
  state.containerRef := Js.Nullable.toOption(containerRef);

let make = (~onEndReached=?, ~offset=0, children) => {
  ...component,
  initialState: () => {containerRef: ref(None)},
  reducer: (action, state) =>
    switch (action) {
    | Scroll =>
      switch (state.containerRef, onEndReached) {
      | ({contents: Some(element)}, Some(onEndReached)) =>
        let scrollHeight = DomRe.Element.scrollHeight(element);
        let scrollTop = DomRe.Element.scrollTop(element);
        let clientHeight = DomRe.Element.clientHeight(element);
        if (scrollTop + clientHeight >= scrollHeight - offset) {
          ReasonReact.SideEffects(((_) => onEndReached()));
        } else {
          ReasonReact.NoUpdate;
        };
      | _ => ReasonReact.NoUpdate
      }
    },
  render: self =>
    <div
      ref=(self.handle(setContainerRef))
      style=(
        ReactDOMRe.Style.make(
          ~overflow="auto",
          ~flexGrow="1",
          ~transform="translateZ(0)",
          (),
        )
      )
      onScroll=((_) => self.send(Scroll))>
      children[0]
    </div>,
};
