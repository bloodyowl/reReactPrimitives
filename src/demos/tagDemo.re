ReactDOMRe.renderToElementWithId(
  <div>
    <Tag name="Some filter name" onPress=(() => ()) />
    <br />
    <div
      style=(
        ReactDOMRe.Style.make(
          ~width="250px",
          ~padding="15px",
          ~backgroundColor="#fffee5",
          (),
        )
      )>
      <Tag
        name="Some really rather long tag name if you consider the horizontal available space"
        color=(226, 82, 74)
        onPress=(() => ())
      />
    </div>
    <br />
  </div>,
  "root",
);
