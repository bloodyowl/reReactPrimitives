ReactDOMRe.renderToElementWithId
  <div>
    <TouchableHighlight onPress=(fun () => ())>
      (ReasonReact.stringToElement "click me!")
    </TouchableHighlight>
    <br />
    <TouchableHighlight
      style=(
        ReactDOMRe.Style.make
          backgroundColor::"#4A90E2"
          padding::"10px"
          color::"#fff"
          borderRadius::"3px"
          overflow::"hidden"
          ()
      )
      onPress=(fun () => ())>
      (ReasonReact.stringToElement "click me!")
    </TouchableHighlight>
  </div>
  "root";
