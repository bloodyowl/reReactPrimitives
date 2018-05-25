ReactDOMRe.renderToElementWithId(
  <div style=(ReactDOMRe.Style.make(~padding="10px", ()))>
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=Right>
      (ReasonReact.string("Right"))
    </Tooltip>
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=Left>
      (ReasonReact.string("Left"))
    </Tooltip>
    <br />
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=Top>
      (ReasonReact.string("Top"))
    </Tooltip>
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=Bottom>
      (ReasonReact.string("Bottom"))
    </Tooltip>
    <br />
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=TopLeft>
      (ReasonReact.string("TopLeft"))
    </Tooltip>
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=TopRight>
      (ReasonReact.string("TopRight"))
    </Tooltip>
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=BottomLeft>
      (ReasonReact.string("BottomLeft"))
    </Tooltip>
    <Tooltip
      style=(
        ReactDOMRe.Style.make(~display="inline-block", ~margin="10px", ())
      )
      message="Helloworld"
      alignTo=BottomRight>
      (ReasonReact.string("BottomRight"))
    </Tooltip>
  </div>,
  "root",
);
