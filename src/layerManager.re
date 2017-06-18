/**
 * This module just makes the way users manage their layers configurable.
 * A layer can be Absolute or Fixed (this matches the CSS equivalent).
 */
type layer;

type behavior =
  | Absolute
  | Fixed;

module type LayerManagerImpl = {
  let make: behavior => layer;
  let render: layer => ReasonReact.reactElement => unit;
  let remove: layer => unit;
};

module Make (Impl: LayerManagerImpl) => {
  /* creates the layer */
  let make behavior => Impl.make behavior;
  /* renders a reactElement in the layer */
  let render layer element => Impl.render layer element;
  /* unmounts the reactElement and deletes the layer */
  let remove layer => Impl.remove layer;
};
