/**
 * This module just makes the way users manage their layers configurable.
 * A layer can be Absolute or Fixed (this matches the CSS equivalent).
 */
type layer = string;

type behavior =
  | Absolute
  | Fixed;

module type LayerManagerImpl = {
  let make: behavior => layer;
  let render: layer => ReasonReact.reactElement => unit;
  let remove: layer => unit;
};

external getStyle : DomRe.Element.t => Dom.cssStyleDeclaration = "style" [@@bs.get];

module DefaultImpl = {
  module LayerMap = Map.Make String;
  let currentLayer = ref 0;
  let map = ref LayerMap.empty;
  let make behavior => {
    let root = DomRe.Document.createElement "div" DomRe.document;
    let style = getStyle root;
    CssStyleDeclarationRe.setProperty
      "position"
      (
        switch behavior {
        | Absolute => "absolute"
        | Fixed => "fixed"
        }
      )
      ""
      style;
    CssStyleDeclarationRe.setProperty "left" "0" "" style;
    CssStyleDeclarationRe.setProperty "top" "0" "" style;
    CssStyleDeclarationRe.setProperty "width" "100vw" "" style;
    CssStyleDeclarationRe.setProperty "height" "100vh" "" style;
    CssStyleDeclarationRe.setProperty "display" "flex" "" style;
    CssStyleDeclarationRe.setProperty "flex-direction" "column" "" style;
    CssStyleDeclarationRe.setProperty "align-items" "center" "" style;
    CssStyleDeclarationRe.setProperty "justify-content" "flex-start" "" style;
    let body = DomRe.Document.querySelector "body" DomRe.document;
    switch body {
    | Some body => DomRe.Element.appendChild root body
    | None => ()
    };
    let layer = !currentLayer + 1;
    currentLayer := layer;
    map := LayerMap.add (string_of_int !currentLayer) root !map;
    string_of_int layer
  };
  let render layer element =>
    try {
      let layerNode = LayerMap.find layer !map;
      ReactDOMRe.render element layerNode
    } {
    | Not_found => ()
    };
  let remove layer =>
    try {
      let layerNode = LayerMap.find layer !map;
      ReactDOMRe.unmountComponentAtNode layerNode;
      DomRe.Element.remove layerNode;
      map := LayerMap.remove layer !map
    } {
    | Not_found => ()
    };
};

module Make (Impl: LayerManagerImpl) => {
  /* creates the layer */
  let make behavior => Impl.make behavior;
  /* renders a reactElement in the layer */
  let render layer element => Impl.render layer element;
  /* unmounts the reactElement and deletes the layer */
  let remove layer => Impl.remove layer;
};
