type state = {containerRef: ref (option Dom.element)};

let component = ReasonReact.statefulComponent "ScrollView";

let setContainerRef containerRef {ReasonReact.state: state} =>
  state.containerRef := Js.Null.to_opt containerRef;

let make ::onEndReached=? ::offset=0 children => {
  let handleScroll _event {ReasonReact.state: state} =>
    switch (state.containerRef, onEndReached) {
    | ({contents: Some element}, Some onEndReached) =>
      let scrollHeight = DomRe.Element.scrollHeight element;
      let scrollTop = DomRe.Element.scrollTop element;
      let clientHeight = DomRe.Element.clientHeight element;
      if (scrollTop + clientHeight >= scrollHeight - offset) {
        onEndReached ()
      };
      ReasonReact.NoUpdate
    | _ => ReasonReact.NoUpdate
    };
  {
    ...component,
    initialState: fun () => {containerRef: ref None},
    render: fun self =>
      <div
        ref=(self.handle setContainerRef)
        style=(ReactDOMRe.Style.make overflow::"auto" flexGrow::"1" ())
        onScroll=(self.update handleScroll)>
        children.(0)
      </div>
  }
};
