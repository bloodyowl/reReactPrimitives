let component = ReasonReact.statelessComponent("Tag");

let tupleToColor = ((r, g, b), ~alpha=1.0, ()) => {
  let (prefix, alphaValue) =
    switch (alpha) {
    | 1.0 => ("rgb(", ")")
    | _ => ("rgba(", "," ++ string_of_float(alpha) ++ ")")
    };
  prefix
  ++ string_of_int(r)
  ++ ","
  ++ string_of_int(g)
  ++ ","
  ++ string_of_int(b)
  ++ alphaValue;
};

module Styles = {
  let root =
    ReactDOMRe.Style.make(
      ~display="inline-flex",
      ~alignItems="center",
      ~boxSizing="borderBox",
      ~maxWidth="100%",
      ~height="30px",
      ~paddingRight="7px",
      ~borderRadius="24px",
      ()
    );
  let name =
    ReactDOMRe.Style.make(
      ~padding="0 10px",
      ~overflow="hidden",
      ~whiteSpace="nowrap",
      ~textOverflow="ellipsis",
      ~fontSize="12px",
      ()
    );
  let button =
    ReactDOMRe.Style.make(
      ~flexShrink="0",
      ~width="18px",
      ~height="18px",
      ~lineHeight="18px",
      ~textAlign="center",
      ~fontSize="12px",
      ~color="#fff",
      ~borderRadius="9px",
      ()
    );
};

let make = (~name, ~color=(74, 144, 226), ~onPress, _children) => {
  let solidColor = tupleToColor(color, ());
  let washedColor = tupleToColor(color, ~alpha=0.17, ());
  {
    ...component,
    render: _self =>
      <div
        style=(
          ReactDOMRe.Style.combine(
            Styles.root,
            ReactDOMRe.Style.make(
              ~border="1px solid " ++ solidColor,
              ~backgroundColor=washedColor,
              ()
            )
          )
        )>
        <span
          style=(
            ReactDOMRe.Style.combine(
              Styles.name,
              ReactDOMRe.Style.make(~color=solidColor, ())
            )
          )>
          (ReasonReact.stringToElement(name))
        </span>
        <TouchableOpacity
          style=(
            ReactDOMRe.Style.combine(
              Styles.button,
              ReactDOMRe.Style.make(~backgroundColor=solidColor, ())
            )
          )
          onPress>
          (ReasonReact.stringToElement({js|✕|js}))
        </TouchableOpacity>
      </div>
  };
};
