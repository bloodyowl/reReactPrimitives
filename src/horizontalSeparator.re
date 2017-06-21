let component = ReasonReact.statelessComponent "HorizontalSeparator";

let make ::color="rgba(0, 0, 0, 0.1)" ::padding="5px 0" _ => {
  ...component,
  render: fun () _self =>
    <div
      style=(ReactDOMRe.Style.make borderBottom::("1px solid " ^ color) ::padding width::"100%" ())
    />
};
