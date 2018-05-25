ReactDOMRe.renderToElementWithId(
  <div>
    <TouchableOpacity onPress=(() => Js.log("onPress"))>
      (ReasonReact.string("click me!"))
    </TouchableOpacity>
    <br />
    <p>
      (ReasonReact.string("Can be inlined"))
      <TouchableOpacity
        style=(ReactDOMRe.Style.make(~display="inline", ()))
        onPress=(() => Js.log("onPress"))>
        (ReasonReact.string("click me!"))
      </TouchableOpacity>
      (ReasonReact.string("like this"))
    </p>
  </div>,
  "root",
);
