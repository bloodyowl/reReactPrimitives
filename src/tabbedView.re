type state = int;

let component = ReasonReact.statefulComponent "TabbedView";

type mode =
  | Horizontal
  | Vertical;

let make ::initiallyOpenedTab=0 ::mode=Vertical ::tabs _children => {
  let setActiveTab index _ _state _self => ReasonReact.Update index;
  let renderTab state self index (tabTitle, _renderChild) =>
    <TouchableOpacity
      style=(
        ReactDOMRe.Style.make
          color::(index === state ? "#4990E2" : "rgba(0, 0, 0, 0.6)")
          padding::"15px 20px"
          boxShadow::(
            index === state ?
              switch mode {
              | Vertical => "0 1px #4990E2"
              | Horizontal => "1px 0 #4990E2"
              } :
              ""
          )
          ()
      )
      onPress=(self.ReasonReact.update (setActiveTab index))>
      tabTitle
    </TouchableOpacity>;
  {
    ...component,
    initialState: fun () => initiallyOpenedTab,
    render: fun state self =>
      <div
        style=(
          ReactDOMRe.Style.make
            display::"flex"
            flexGrow::"1"
            flexDirection::(
              switch mode {
              | Horizontal => "row"
              | Vertical => "column"
              }
            )
            ()
        )>
        <div
          style=(
            ReactDOMRe.Style.make
              display::"flex"
              flexGrow::"0"
              flexDirection::(
                switch mode {
                | Horizontal => "column"
                | Vertical => "row"
                }
              )
              justifyContent::(
                switch mode {
                | Horizontal => ""
                | Vertical => "center"
                }
              )
              boxShadow::(
                switch mode {
                | Vertical => "0 1px rgba(0, 0, 0, 0.1)"
                | Horizontal => "1px 0 rgba(0, 0, 0, 0.1)"
                }
              )
              ()
          )>
          (
            tabs |> Array.mapi (renderTab state self) |> ReasonReact.arrayToElement
          )
        </div>
        <div style=(ReactDOMRe.Style.make flexGrow::"1" ())>
          {
            let (_activeTab, renderActiveTab) = tabs.(state);
            renderActiveTab ()
          }
        </div>
      </div>
  }
};
