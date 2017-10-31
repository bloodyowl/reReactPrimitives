type item = {
  label: string,
  description: string
};

let renderItem = (item) =>
  <div
    style=(ReactDOMRe.Style.make(~padding="10px", ~display="flex", ~flexDirection="column", ()))>
    <span style=(ReactDOMRe.Style.make(~fontWeight="700", ()))>
      (ReasonReact.stringToElement(item.label))
    </span>
    <span style=(ReactDOMRe.Style.make(~fontSize="12px", ()))>
      (ReasonReact.stringToElement(item.description))
    </span>
  </div>;

ReactDOMRe.renderToElementWithId(
  <div>
    <ListView
      items=[
        {label: "One", description: "First"},
        {label: "Two", description: "Second"},
        {label: "Three", description: "Third"}
      ]
      renderItem
    />
  </div>,
  "root"
);
