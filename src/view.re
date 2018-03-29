let component = ReasonReact.statelessComponent("View");

let make = (~style=?, children) => {
  ...component,
  render: _self => <div ?style> (ReasonReact.arrayToElement(children)) </div>,
};
