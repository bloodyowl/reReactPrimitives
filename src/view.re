let component = ReasonReact.statelessComponent "View";

let emptyStyle = ReactDOMRe.Style.make ();

let make ::style=? children => {
  ...component,
  render: fun () _self =>
    <div
      style=(
        switch style {
        | Some style => style
        | None => emptyStyle
        }
      )>
      (ReasonReact.arrayToElement children)
    </div>
};
