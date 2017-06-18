let component = ReasonReact.statelessComponent "Text";

let emptyStyle = ReactDOMRe.Style.make ();

let make ::style=? children => {
  ...component,
  render: fun () _self =>
    <span
      style=(
        switch style {
        | Some style => style
        | None => emptyStyle
        }
      )>
      (ReasonReact.arrayToElement children)
    </span>
};
