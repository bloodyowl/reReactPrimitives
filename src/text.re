let component = ReasonReact.statelessComponent("Text");

let make = (~style=?, children) => {
  ...component,
  render: _self => <span ?style> (ReasonReact.array(children)) </span>,
};
