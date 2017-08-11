let rec render firstValue =>
  ReactDOMRe.renderToElementWithId
    <div>
      <Switch value=(Idle, firstValue) onValueChange=render />
      <br />
      <Switch value=(Idle, false) onValueChange=(fun _ => ()) />
      <br />
      <Switch value=(Updating, false) onValueChange=(fun _ => ()) />
      <br />
      <Switch value=(Updating, true) onValueChange=(fun _ => ()) />
    </div>
    "root";

render true;
