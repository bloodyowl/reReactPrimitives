ReactDOMRe.renderToElementWithId(
  <div>
    <Button onPress=(() => ()) title="click me!" color="#fb5" />
    <br />
    <br />
    <Button onPress=(() => ()) title="click me!" color="#4A90E2" />
    (ReasonReact.stringToElement(" "))
    <Button onPress=(() => ()) title="click me!" color="#7ED321" />
    <br />
    <Button onPress=(() => ()) title="click me! (disabled)" color="#C30" disabled=true />
  </div>,
  "root"
);
