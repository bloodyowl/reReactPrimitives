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
    </div>,
    "root"
  );

render(true);
