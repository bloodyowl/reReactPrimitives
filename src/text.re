let component = ReasonReact.statelessComponent "Text";

let make ::style=? children => {
  ...component,
  render: fun _self => <span style=?style> (ReasonReact.arrayToElement children) </span>
};
