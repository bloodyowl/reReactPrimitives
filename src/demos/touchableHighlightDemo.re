ReactDOMRe.renderToElementWithId(
  <div>
    <TouchableHighlight onPress=(() => Js.log("onPress"))>
      (ReasonReact.string("click me!"))
    </TouchableHighlight>
    <br />
    <TouchableHighlight
      style=(
        ReactDOMRe.Style.make(
          ~backgroundColor="#4A90E2",
          ~padding="10px",
          ~color="#fff",
          ~borderRadius="3px",
          ~overflow="hidden",
          (),
        )
      )
      onPress=(() => Js.log("onPress"))>
      (ReasonReact.string("click me!"))
    </TouchableHighlight>
  </div>,
  "root",
);
