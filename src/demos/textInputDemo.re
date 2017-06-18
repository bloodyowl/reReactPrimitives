type demoState = {
  one: string,
  two: string,
  three: string
};

let rec render state =>
  ReactDOMRe.renderToElementWithId
    <div>
      <TextInput
        onTextChange=(fun one => render {...state, one})
        value=state.one
        style=(ReactDOMRe.Style.make fontSize::"20px" color::"#666" ())
      />
      <br />
      <TextInput
        onTextChange=(fun two => render {...state, two})
        value=state.two
        multiline=true
        rows=5
        style=(ReactDOMRe.Style.make fontSize::"20px" color::"#666" ())
      />
      <br />
      <TextInput
        onTextChange=(fun three => render {...state, three})
        value=state.three
        multiline=true
        autoSize=true
        style=(ReactDOMRe.Style.make fontSize::"20px" color::"#666" ())
      />
    </div>
    "root";

render {one: "", two: "", three: ""};
