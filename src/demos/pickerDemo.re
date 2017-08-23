let renderOption option value =>
  <div
    style=(
      ReactDOMRe.Style.make
        padding::"10px"
        borderBottom::"1px solid rgba(0, 0, 0, 0.1)"
        backgroundColor::(
          switch value {
          | Some value => value == option ? "#4A90E2" : ""
          | _ => ""
          }
        )
        color::(
          switch value {
          | Some value => value == option ? "#fff" : ""
          | _ => ""
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
      <Picker
        value
        disabled=true
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
