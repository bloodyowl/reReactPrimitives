let component = ReasonReact.statelessComponent("Button");

let buttonGroupStyle =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flexDirection="row",
    ~alignItems="center",
    ~borderRadius="3px",
    ~overflow="hidden",
    (),
  );

let addKey = (index, item) => <div key=(string_of_int(index))> item </div>;

let make = (~style=?, children) => {
  ...component,
  render: _self =>
    <div
      style=(
        switch (style) {
        | Some(style) => ReactDOMRe.Style.combine(buttonGroupStyle, style)
        | None => buttonGroupStyle
        }
      )>
      (children |> Array.mapi(addKey) |> ReasonReact.array)
    </div>,
};
