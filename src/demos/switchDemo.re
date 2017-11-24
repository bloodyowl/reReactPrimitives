let rec render = (firstValue) =>
  ReactDOMRe.renderToElementWithId(
    <div>
      <Switch value=(Idle, firstValue) onValueChange=render />
      <br />
      <Switch value=(Idle, false) onValueChange=((_) => ()) />
      <br />
      <Switch value=(Updating, false) onValueChange=((_) => ()) />
      <br />
      <Switch value=(Updating, true) onValueChange=((_) => ()) />
      <br />
      (ReasonReact.stringToElement("disabled:"))
      <Switch value=(Idle, firstValue) disabled=true onValueChange=render />
    </div>,
    "root"
  );

render(true);
