let component = ReasonReact.statelessComponent "HorizontalSeparator";

let make ::color="rgba(0, 0, 0, 0.1)" _ => {
  ...component,
  render: fun () _self =>
    <div style=(ReactDOMRe.Style.make borderBottom::("1px solid " ^ color) width::"100%" ()) />
};
