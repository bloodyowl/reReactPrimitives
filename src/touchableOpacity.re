type state =
  | Depressed
  | Idle;

let component = ReasonReact.statefulComponent "TouchableOpacity";

let make ::onPress ::style=? children => {
  let handleMouseDown _event _ => ReasonReact.Update Depressed;
  let handleMouseUp _event _ => ReasonReact.Update Idle;
  let handleClick _event _ => {
    onPress ();
    ReasonReact.NoUpdate
  };
  {
    ...component,
    initialState: fun _ => Idle,
    render: fun ({state} as self) => {
      let opacityStyle =
        ReactDOMRe.Style.make
          transition::"100ms linear opacity"
          transform::"translateZ(0)"
          cursor::"pointer"
          opacity::(
            switch state {
            | Depressed => "0.5"
            | Idle => "1"
            }
          )
          ();
      <div
        role="button"
        style=(
          switch style {
          | None => opacityStyle
          | Some style => ReactDOMRe.Style.combine style opacityStyle
          }
        )
        onMouseDown=(self.update handleMouseDown)
        onMouseUp=(self.update handleMouseUp)
        onClick=(self.update handleClick)>
        children.(0)
      </div>
    }
  }
};
