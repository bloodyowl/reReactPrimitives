let component = ReasonReact.statelessComponent "View";

let make ::style=? children => {
  ...component,
  render: fun _self => <div style=?style> (ReasonReact.arrayToElement children) </div>
};
