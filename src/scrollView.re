type state = {containerRef: option Dom.element};

let component = ReasonReact.statefulComponent "ScrollView";

let make ::onEndReached=? ::offset=0 children => {
  let setContainerRef containerRef _self =>
    switch (Js.Null.to_opt containerRef) {
    | Some containerRef => ReasonReact.SilentUpdate {containerRef: Some containerRef}
    | None => ReasonReact.NoUpdate
    };
  let handleScroll _event {ReasonReact.state: state} =>
    switch (state.containerRef, onEndReached) {
    | (Some element, Some onEndReached) =>
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
    initialState: fun () => {containerRef: None},
    render: fun self =>
      <div
        ref=(self.update setContainerRef)
        style=(ReactDOMRe.Style.make overflow::"auto" flexGrow::"1" ())
        onScroll=(self.update handleScroll)>
        children.(0)
      </div>
  }
};
