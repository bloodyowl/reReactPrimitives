type mode =
  | Horizontal
  | Vertical;

type state = {
  openTab: int,
  activeTabHandleRect: option (int, int, int, int),
  tabContainerRef: ref (option DomRe.Element.t)
};

type action =
  | SetActiveTab int
  | MeasureRect;

let component = ReasonReact.reducerComponent "TabbedView";

let setTabContainerRef tabContainerRef {ReasonReact.state: state} =>
  state.tabContainerRef := Js.Null.to_opt tabContainerRef;

let setRect state =>
  switch state.tabContainerRef {
  | {contents: Some containerRef} =>
    let children = DomRe.Element.children containerRef;
    let item = DomRe.HtmlCollection.item state.openTab children;
    switch item {
    | Some child =>
      let parentRect = DomRe.Element.getBoundingClientRect containerRef;
      let childRect = DomRe.Element.getBoundingClientRect child;
      ReasonReact.Update {
        ...state,
        activeTabHandleRect:
          Some (
            DomRectRe.left childRect - DomRectRe.left parentRect,
            DomRectRe.top childRect - DomRectRe.top parentRect,
            DomRectRe.width childRect,
            DomRectRe.height childRect
          )
      }
    | None => ReasonReact.NoUpdate
    }
  | _ => ReasonReact.NoUpdate
  };

let measureRectAtNextFrame {ReasonReact.reduce: reduce} =>
  Bs_webapi.requestAnimationFrame (fun _ => reduce (fun () => MeasureRect) ());

let make
    ::initiallyOpenTab=0
    ::mode=Vertical
    ::tabs
    ::color="#4A90E2"
    ::tabHeadingPadding="15px 20px"
    _children => {
  ...component,
  initialState: fun () => {
    openTab: initiallyOpenTab,
    activeTabHandleRect: None,
    tabContainerRef: ref None
  },
  didMount: fun _ => ReasonReact.SideEffects measureRectAtNextFrame,
  reducer: fun action state =>
    switch action {
    | SetActiveTab openTab =>
      ReasonReact.UpdateWithSideEffects {...state, openTab} measureRectAtNextFrame
    | MeasureRect => setRect state
    },
  render: fun {state, reduce, handle} =>
    <div
      style=(
        ReactDOMRe.Style.make
          display::"flex"
          flexGrow::"1"
          flexDirection::(
            switch mode {
            | Horizontal => "row"
            | Vertical => "column"
            }
          )
          ()
      )>
      <div
        style=(
          ReactDOMRe.Style.make
            position::"relative" display::"flex" flexGrow::"0" flexShrink::"0" ()
        )>
        <div
          ref=(handle setTabContainerRef)
          style=(
            ReactDOMRe.Style.make
              display::"flex"
              flexGrow::"1"
              flexDirection::(
                switch mode {
                | Horizontal => "column"
                | Vertical => "row"
                }
              )
              justifyContent::(
                switch mode {
                | Horizontal => ""
                | Vertical => "center"
                }
              )
              boxShadow::(
                switch mode {
                | Vertical => "0 1px rgba(0, 0, 0, 0.1)"
                | Horizontal => "1px 0 rgba(0, 0, 0, 0.1)"
                }
              )
              ()
          )>
          (
            tabs
            |> Array.mapi (
                 fun index (tabTitle, _) =>
                   <TouchableOpacity
                     key=(string_of_int index)
                     style=(
                       ReactDOMRe.Style.make
                         color::(index === state.openTab ? color : "rgba(0, 0, 0, 0.6)")
                         padding::tabHeadingPadding
                         ()
                     )
                     onPress=(reduce (fun _ => SetActiveTab index))>
                     tabTitle
                   </TouchableOpacity>
               )
            |> ReasonReact.arrayToElement
          )
        </div>
        (
          switch (mode, state.activeTabHandleRect) {
          | (Vertical, Some (x, _y, w, _h)) =>
            <div
              style=(
                ReactDOMRe.Style.make
                  position::"absolute"
                  transition::"200ms ease-out all"
                  bottom::"-1px"
                  left::(string_of_int x ^ "px")
                  width::(string_of_int w ^ "px")
                  height::"2px"
                  backgroundColor::color
                  ()
              )
            />
          | (Horizontal, Some (_x, y, _w, h)) =>
            <div
              style=(
                ReactDOMRe.Style.make
                  position::"absolute"
                  transition::"200ms ease-out all"
                  right::"-1px"
                  top::(string_of_int y ^ "px")
                  height::(string_of_int h ^ "px")
                  width::"2px"
                  backgroundColor::color
                  ()
              )
            />
          | _ => ReasonReact.nullElement
          }
        )
      </div>
      <div style=(ReactDOMRe.Style.make flexGrow::"1" display::"flex" flexDirection::"column" ())>
        {
          let (_activeTab, renderActiveTab) = tabs.(state.openTab);
          renderActiveTab ()
        }
      </div>
    </div>
};
