type state = {containerRef: option Dom.element};

let component = ReasonReact.statefulComponent "ScrollView";

let make ::onEndReached ::offset=0 children => {
  let setContainerRef containerRef _state _self =>
    switch (Js.Null.to_opt containerRef) {
    | Some containerRef => ReasonReact.SilentUpdate {containerRef: Some containerRef}
    | None => ReasonReact.NoUpdate
    };
  let handleScroll _event state _self =>
    switch state.containerRef {
    | Some element =>
      let scrollHeight = DomRe.Element.scrollHeight element;
      let scrollTop = DomRe.Element.scrollTop element;
      let clientHeight = DomRe.Element.clientHeight element;
      if (scrollTop + clientHeight >= scrollHeight - offset) {
        onEndReached ()
      };
      ReasonReact.NoUpdate
    | None => ReasonReact.NoUpdate
    };
  {
    ...component,
    initialState: fun () => {containerRef: None},
    render: fun _state self =>
      <div
        ref=(self.update setContainerRef)
        style=(ReactDOMRe.Style.make overflow::"auto" flexGrow::"1" ())
        onScroll=(self.update handleScroll)>
        (children |> ReasonReact.arrayToElement)
      </div>
  }
};
