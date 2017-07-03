/**
 * This module just makes the way users manage their layers configurable.
 * A layer can be Absolute or Fixed (this matches the CSS equivalent).
 */
type layer = string;

type align =
  | TopLeft
  | TopRight
  | BottomLeft
  | BottomRight
  | Left
  | Right
  | Top
  | Bottom;

type behavior =
  | FullViewport
  | Contextualized DomRe.Element.t align
  | Fixed;

module type LayerManagerImpl = {
  let make: behavior => Js.Promise.t layer;
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
    switch behavior {
    | FullViewport =>
      CssStyleDeclarationRe.setProperty "position" "absolute" "" style;
      CssStyleDeclarationRe.setProperty "z-index"  "2147483647" "" style;
      CssStyleDeclarationRe.setProperty
        "left" (string_of_int (WindowRe.pageXOffset DomRe.window) ^ "px") "" style;
      CssStyleDeclarationRe.setProperty
        "top" (string_of_int (WindowRe.pageYOffset DomRe.window) ^ "px") "" style
    | Contextualized element align =>
      let pageXOffset = WindowRe.pageXOffset DomRe.window;
      let pageYOffset = WindowRe.pageYOffset DomRe.window;
      let innerWidth = WindowRe.innerWidth DomRe.window;
      let innerHeight = WindowRe.innerHeight DomRe.window;
      let boundaries = DomRe.Element.getBoundingClientRect element;
      CssStyleDeclarationRe.setProperty "position" "absolute" "" style;
      CssStyleDeclarationRe.setProperty "z-index"  "2147483647" "" style;
      switch align {
      | TopLeft =>
        CssStyleDeclarationRe.setProperty
          "bottom"
          (string_of_int (innerHeight + pageYOffset - DomRectRe.top boundaries) ^ "px")
          ""
          style;
        CssStyleDeclarationRe.setProperty
          "left" (string_of_int (pageXOffset + DomRectRe.left boundaries) ^ "px") "" style
      | TopRight =>
        CssStyleDeclarationRe.setProperty
          "bottom"
          (string_of_int (innerHeight + pageYOffset - DomRectRe.top boundaries) ^ "px")
          ""
          style;
        CssStyleDeclarationRe.setProperty
          "right"
          (string_of_int (innerWidth + pageXOffset - DomRectRe.right boundaries) ^ "px")
          ""
          style
      | BottomLeft =>
        CssStyleDeclarationRe.setProperty
          "top" (string_of_int (pageYOffset + DomRectRe.bottom boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "left" (string_of_int (pageXOffset + DomRectRe.left boundaries) ^ "px") "" style
      | BottomRight =>
        CssStyleDeclarationRe.setProperty
          "top" (string_of_int (pageYOffset + DomRectRe.bottom boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "right"
          (string_of_int (innerWidth + pageXOffset - DomRectRe.right boundaries) ^ "px")
          ""
          style
      | Left =>
        CssStyleDeclarationRe.setProperty
          "top" (string_of_int (pageYOffset + DomRectRe.top boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "right"
          (string_of_int (innerWidth + pageXOffset - DomRectRe.left boundaries) ^ "px")
          ""
          style;
        CssStyleDeclarationRe.setProperty
          "height" (string_of_int (DomRectRe.height boundaries) ^ "px") "" style
      | Right =>
        CssStyleDeclarationRe.setProperty
          "top" (string_of_int (pageYOffset + DomRectRe.top boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "left" (string_of_int (pageXOffset + DomRectRe.right boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "height" (string_of_int (DomRectRe.height boundaries) ^ "px") "" style
      | Top =>
        CssStyleDeclarationRe.setProperty
          "bottom"
          (string_of_int (innerHeight + pageYOffset - DomRectRe.top boundaries) ^ "px")
          ""
          style;
        CssStyleDeclarationRe.setProperty
          "left" (string_of_int (pageXOffset + DomRectRe.left boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "min-width" (string_of_int (DomRectRe.width boundaries) ^ "px") "" style
      | Bottom =>
        CssStyleDeclarationRe.setProperty
          "top" (string_of_int (pageYOffset + DomRectRe.bottom boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "left" (string_of_int (pageXOffset + DomRectRe.left boundaries) ^ "px") "" style;
        CssStyleDeclarationRe.setProperty
          "min-width" (string_of_int (DomRectRe.width boundaries) ^ "px") "" style
      }
    | Fixed =>
      CssStyleDeclarationRe.setProperty "position" "fixed" "" style;
      CssStyleDeclarationRe.setProperty "z-index"  "2147483647" "" style;
      CssStyleDeclarationRe.setProperty "left" "0" "" style;
      CssStyleDeclarationRe.setProperty "top" "0" "" style
    };
    let body = DomRe.Document.querySelector "body" DomRe.document;
    switch body {
    | Some body => DomRe.Element.appendChild root body
    | None => ()
    };
    let layer = !currentLayer + 1;
    currentLayer := layer;
    map := LayerMap.add (string_of_int !currentLayer) root !map;
    Js.Promise.resolve (string_of_int layer)
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
