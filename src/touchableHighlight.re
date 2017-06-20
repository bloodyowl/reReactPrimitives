type state =
  | Depressed
  | Idle;

let component = ReasonReact.statefulComponent "TouchableHighlight";

module Styles = {
  let container = ReactDOMRe.Style.make position::"relative" cursor::"pointer" ();
  let contents = ReactDOMRe.Style.make position::"relative" ();
};

let make ::onPress ::underlayColor="rgba(0, 0, 0, 0.2)" ::style=? children => {
  let handleMouseDown _event _self _state => ReasonReact.Update Depressed;
  let handleMouseUp _event _self _state => ReasonReact.Update Idle;
  let handleClick _event _self _state => {
    onPress ();
    ReasonReact.NoUpdate
  };
  {
    ...component,
    initialState: fun _ => Idle,
    render: fun state self =>
      <div
        role="button"
        style=(
          switch style {
          | None => Styles.container
          | Some style => ReactDOMRe.Style.combine style Styles.container
          }
        )
        onMouseDown=(self.update handleMouseDown)
        onMouseUp=(self.update handleMouseUp)
        onClick=(self.update handleClick)>
        (
          switch state {
          | Depressed =>
            <div
              style=(
                ReactDOMRe.Style.make
                  position::"absolute"
                  top::"0"
                  left::"0"
                  right::"0"
                  bottom::"0"
                  backgroundColor::underlayColor
                  ()
              )
            />
          | Idle => ReasonReact.nullElement
          }
        )
        <div style=Styles.contents> children.(0) </div>
      </div>
  }
};
