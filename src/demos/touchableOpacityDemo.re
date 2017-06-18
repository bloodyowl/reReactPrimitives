ReactDOMRe.renderToElementWithId
  <div>
    <TouchableOpacity onPress=(fun () => ())>
      (ReasonReact.stringToElement "click me!")
    </TouchableOpacity>
    <br />
    <p>
      (ReasonReact.stringToElement "Can be inlined")
      <TouchableOpacity tag="span" onPress=(fun () => ())>
        (ReasonReact.stringToElement "click me!")
      </TouchableOpacity>
      (ReasonReact.stringToElement "like this")
    </p>
  </div>
  "root";
