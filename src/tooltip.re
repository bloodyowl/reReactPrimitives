type state = option LayerManager.layer;

let component = ReasonReact.statefulComponent "Tooltip";

module TooltipLayerManager = LayerManager.Make LayerManager.DefaultImpl;

let getArrowStyle (alignTo: LayerManager.align) =>
  switch alignTo {
  | TopLeft
  | Top =>
    ReactDOMRe.Style.make
      position::"absolute"
      width::"0"
      height::"0"
      border::"5px solid transparent"
      borderTopColor::"#000"
      borderBottomWidth::"0"
      left::"5px"
      top::"100%"
      ()
  | TopRight =>
    ReactDOMRe.Style.make
      position::"absolute"
      width::"0"
      height::"0"
      border::"5px solid transparent"
      borderTopColor::"#000"
      borderBottomWidth::"0"
      right::"5px"
      top::"100%"
      ()
  | Right =>
    ReactDOMRe.Style.make
      position::"absolute"
      width::"0"
      height::"0"
      border::"5px solid transparent"
      borderRightColor::"#000"
      borderLeftWidth::"0"
      right::"100%"
      top::"5px"
      ()
  | Bottom
  | BottomLeft =>
    ReactDOMRe.Style.make
      position::"absolute"
      width::"0"
      height::"0"
      border::"5px solid transparent"
      borderBottomColor::"#000"
      borderTopWidth::"0"
      left::"5px"
      bottom::"100%"
      ()
  | BottomRight =>
    ReactDOMRe.Style.make
      position::"absolute"
      width::"0"
      height::"0"
      border::"5px solid transparent"
      borderBottomColor::"#000"
      borderTopWidth::"0"
      right::"5px"
      bottom::"100%"
      ()
  | Left =>
    ReactDOMRe.Style.make
      position::"absolute"
      width::"0"
      height::"0"
      border::"5px solid transparent"
      borderLeftColor::"#000"
      borderRightWidth::"0"
      left::"100%"
      top::"5px"
      ()
  };

let make ::style=? ::message alignTo::(alignTo: LayerManager.align) children => {
  let whenLayerReady layer _self => {
    TooltipLayerManager.render
      layer
      <div
        style=(
          ReactDOMRe.Style.make
            borderRadius::"2px"
            backgroundColor::"#000"
            position::"relative"
            color::"#fff"
            padding::"10px"
            fontSize::"12px"
            margin::(
              switch alignTo {
              | Left
              | Right => "0 10px"
              | _ => "10px 0"
              }
            )
            ()
        )>
        <div style=(getArrowStyle alignTo) />
        (ReasonReact.stringToElement message)
      </div>;
    ReasonReact.SilentUpdate (Some layer)
  };
  let showTooltip event self => {
    let layer =
      TooltipLayerManager.make (Contextualized (ReactEventRe.Mouse.target event) alignTo);
    ignore (
      Js.Promise.then_
        (
          fun layer => {
            self.ReasonReact.update whenLayerReady layer;
            Js.Promise.resolve ()
          }
        )
        layer
    );
    ReasonReact.NoUpdate
  };
  let hideTooltip _event {ReasonReact.state} =>
    switch state {
    | Some layer =>
      TooltipLayerManager.remove layer;
      ReasonReact.SilentUpdate None
    | None => ReasonReact.NoUpdate
    };
  {
    ...component,
    initialState: fun () => None,
    render: fun self =>
      <div
        style=?style onMouseEnter=(self.update showTooltip) onMouseLeave=(self.update hideTooltip)>
        children.(0)
      </div>
  }
};
