let component = ReasonReact.statelessComponent "Switch";

type status =
  | Idle
  | Updating;

type value = (status, bool);

let make ::value ::onValueChange _children => {
  let handleChange _event => {
    let (_state, value) = value;
    onValueChange (not value)
  };
  {
    ...component,
    render: fun () _self =>
      <div
        onClick=handleChange
        style=(
          ReactDOMRe.Style.make
            width::"35px"
            height::"14px"
            borderRadius::"7px"
            boxShadow::"inset 0 0 0 1px rgba(0, 0, 0, 0.1)"
            position::"relative"
            cursor::"pointer"
            backgroundColor::(
              switch value {
              | (Idle, true) => "rgba(74, 144, 226, 1)"
              | (Idle, false) => "rgba(0, 0, 0, 0.2)"
              | (Updating, true) => "rgba(74, 144, 226, 0.5)"
              | (Updating, false) => "rgba(0, 0, 0, 0.1)"
              }
            )
            ()
        )>
        <div
          style=(
            ReactDOMRe.Style.make
              width::"20px"
              height::"20px"
              backgroundColor::"#fff"
              boxShadow::"0 0 0 1px rgba(0, 0, 0, 0.1), 0 2px 4px rgba(0, 0, 0, 0.1)"
              position::"absolute"
              borderRadius::"10px"
              top::"-3px"
              transition::"200ms left ease-in-out"
              display::"flex"
              flexDirection::"row"
              alignItems::"center"
              justifyContent::"center"
              left::(
                switch value {
                | (_, true) => "20px"
                | (_, false) => "-5px"
                }
              )
              ()
          )>
          (
            switch value {
            | (Idle, _) => ReactRe.nullElement
            | (Updating, _) =>
              <ActivityIndicator size=14.0 color=(200, 200, 200) />
            }
          )
        </div>
      </div>
  }
};
