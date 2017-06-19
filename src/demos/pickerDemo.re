let renderOption option value =>
  <div
    style=(
      ReactDOMRe.Style.make
        padding::"10px"
        borderBottom::"1px solid rgba(0, 0, 0, 0.1)"
        fontWeight::(
          switch value {
          | Some value => value == option ? "700" : "400"
          | _ => "400"
          }
        )
        ()
    )>
    (ReasonReact.stringToElement option)
  </div>;

let rec render value =>
  ReactDOMRe.renderToElementWithId
    <div style=(ReactDOMRe.Style.make padding::"10px" ())>
      <Picker
        value
        renderPicker=(
          fun value =>
            switch value {
            | Some value => ReasonReact.stringToElement value
            | None => ReasonReact.stringToElement {js|Select a value …|js}
            }
        )
        renderOption
        options=["One", "Two", "Three"]
        onValueChange=render
      />
    </div>
    "root";

render None;
