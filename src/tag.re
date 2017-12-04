let component = ReasonReact.statelessComponent("Tag");

let tupleToColor = ((r, g, b), ~alpha=1.0, ()) => {
  let (prefix, alphaValue) =
    switch alpha {
    | 1.0 => ("rgb(", ")")
    | _ => ("rgba(", "," ++ string_of_float(alpha) ++ ")")
    };
  prefix ++ string_of_int(r) ++ "," ++ string_of_int(g) ++ "," ++ string_of_int(b) ++ alphaValue
};

module Styles = {
  let root = (color) =>
    ReactDOMRe.Style.make(
      ~display="inline-flex",
      ~alignItems="center",
      ~boxSizing="borderBox",
      ~border="1px solid " ++ tupleToColor(color, ()),
      ~maxWidth="100%",
      ~height="30px",
      ~paddingRight="7px",
      ~backgroundColor=tupleToColor(color, ~alpha=0.17, ()),
      ~borderRadius="24px",
      ()
    );
  let name = (color) =>
    ReactDOMRe.Style.make(
      ~padding="0 10px",
      ~overflow="hidden",
      ~whiteSpace="nowrap",
      ~textOverflow="ellipsis",
      ~fontSize="12px",
      ~color=tupleToColor(color, ()),
      ()
    );
  let button = (color) =>
    ReactDOMRe.Style.make(
      ~flexShrink="0",
      ~width="18px",
      ~height="18px",
      ~lineHeight="18px",
      ~textAlign="center",
      ~fontSize="12px",
      ~color="#fff",
      ~backgroundColor=tupleToColor(color, ()),
      ~borderRadius="9px",
      ()
    );
};

let make = (~name, ~color=(74, 144, 226), ~onPress, _children) => {
  ...component,
  render: (_self) =>
    <div style=(Styles.root(color))>
      <span style=(Styles.name(color))> (ReasonReact.stringToElement(name)) </span>
      <TouchableOpacity style=(Styles.button(color)) onPress>
        (ReasonReact.stringToElement({js|✕|js}))
      </TouchableOpacity>
    </div>
};
