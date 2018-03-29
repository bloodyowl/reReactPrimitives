type state = option(LayerManager.layer);

type action =
  | SetLayer(LayerManager.layer)
  | RemoveLayer;

let component = ReasonReact.reducerComponent("Tooltip");

module TooltipLayerManager = LayerManager.Make(LayerManager.DefaultImpl);

let getArrowStyle = (alignTo: LayerManager.align) =>
  switch (alignTo) {
  | TopLeft
  | Top =>
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~width="0",
      ~height="0",
      ~border="5px solid transparent",
      ~borderTopColor="#000",
      ~borderBottomWidth="0",
      ~left="5px",
      ~top="100%",
      (),
    )
  | TopRight =>
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~width="0",
      ~height="0",
      ~border="5px solid transparent",
      ~borderTopColor="#000",
      ~borderBottomWidth="0",
      ~right="5px",
      ~top="100%",
      (),
    )
  | Right =>
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~width="0",
      ~height="0",
      ~border="5px solid transparent",
      ~borderRightColor="#000",
      ~borderLeftWidth="0",
      ~right="100%",
      ~top="5px",
      (),
    )
  | Bottom
  | BottomLeft =>
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~width="0",
      ~height="0",
      ~border="5px solid transparent",
      ~borderBottomColor="#000",
      ~borderTopWidth="0",
      ~left="5px",
      ~bottom="100%",
      (),
    )
  | BottomRight =>
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~width="0",
      ~height="0",
      ~border="5px solid transparent",
      ~borderBottomColor="#000",
      ~borderTopWidth="0",
      ~right="5px",
      ~bottom="100%",
      (),
    )
  | Left =>
    ReactDOMRe.Style.make(
      ~position="absolute",
      ~width="0",
      ~height="0",
      ~border="5px solid transparent",
      ~borderLeftColor="#000",
      ~borderRightWidth="0",
      ~left="100%",
      ~top="5px",
      (),
    )
  };

let renderLayer =
    (~message, ~alignTo: LayerManager.align, {ReasonReact.state}) =>
  switch (state) {
  | Some(layer) =>
    TooltipLayerManager.render(
      layer,
      <div
        style=(
          ReactDOMRe.Style.make(
            ~borderRadius="2px",
            ~backgroundColor="#000",
            ~position="relative",
            ~color="#fff",
            ~padding="10px",
            ~fontSize="12px",
            ~margin=
              switch (alignTo) {
              | Left
              | Right => "0 10px"
              | _ => "10px 0"
              },
            (),
          )
        )>
        <div style=(getArrowStyle(alignTo)) />
        <div style=(ReactDOMRe.Style.make(~whiteSpace="pre-line", ()))>
          (ReasonReact.stringToElement(message))
        </div>
      </div>,
    )
  | None => ()
  };

let make = (~style=?, ~message, ~alignTo: LayerManager.align, children) => {
  let showTooltip = (event, self) => {
    let layer =
      TooltipLayerManager.make(
        Contextualized(ReactEventRe.Mouse.target(event), alignTo),
      );
    ignore(
      Js.Promise.then_(
        layer => {
          self.ReasonReact.send(SetLayer(layer));
          Js.Promise.resolve();
        },
        layer,
      ),
    );
  };
  let hideTooltip = (_event, {ReasonReact.state, ReasonReact.send}) =>
    switch (state) {
    | Some(layer) =>
      TooltipLayerManager.remove(layer);
      send(RemoveLayer);
    | None => ()
    };
  {
    ...component,
    initialState: () => None,
    reducer: (action, _state) =>
      switch (action) {
      | SetLayer(layer) =>
        ReasonReact.SilentUpdateWithSideEffects(
          Some(layer),
          renderLayer(~message, ~alignTo),
        )
      | RemoveLayer => ReasonReact.SilentUpdate(None)
      },
    render: ({handle}) =>
      <div
        ?style
        onMouseEnter=(handle(showTooltip))
        onMouseLeave=(handle(hideTooltip))>
        children[0]
      </div>,
  };
};
