type mySegments =
  | First
  | Second
  | Third;

let segments = [("First", First), ("Second", Second), ("Third", Third)];

let rec render activeSegment =>
  ReactDOMRe.renderToElementWithId
    <div style=(ReactDOMRe.Style.make padding::"10px" ())>
      <SegmentedControl segments activeSegment onSegmentPress=render color="#FE1F69" />
    </div>
    "root";

render First;
