let component = ReasonReact.statelessComponent "Button";

let buttonGroupStyle =
  ReactDOMRe.Style.make
    display::"flex"
    flexDirection::"row"
    alignItems::"center"
    borderRadius::"3px"
    overflow::"hidden"
    ();

let make ::style=? children => {
  ...component,
  render: fun () _self =>
    <div
      style=(
        switch style {
        | Some style => ReactDOMRe.Style.combine buttonGroupStyle style
        | None => buttonGroupStyle
        }
      )>
      (children |> ReasonReact.arrayToElement)
    </div>
};
