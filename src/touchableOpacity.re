type state =
  | Depressed
  | Idle;

let component = ReasonReact.statefulComponent "TouchableOpacity";

let make ::onPress ::style=? ::tag="div" child => {
  let handleMouseDown _event _self _state => ReasonReact.Update Depressed;
  let handleMouseUp _event _self _state => ReasonReact.Update Idle;
  let handleClick _event _self _state => {
    onPress ();
    ReasonReact.NoUpdate
  };
  {
    ...component,
    initialState: fun _ => Idle,
    render: fun state self => {
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
      ReactDOMRe.createElement
        tag
        props::(
          ReactDOMRe.props
            role::"button"
            style::(
              switch style {
              | None => opacityStyle
              | Some style => ReactDOMRe.Style.combine style opacityStyle
              }
            )
            onMouseDown::(self.update handleMouseDown)
            onMouseUp::(self.update handleMouseUp)
            onClick::(self.update handleClick)
            ()
        )
        [|ReasonReact.arrayToElement child|]
    }
  }
};
