type state = {
  openTab: int,
  activeTabHandleRect: option (int, int, int, int),
  tabContainerRef: option DomRe.Element.t
};

let component = ReasonReact.statefulComponent "TabbedView";

type mode =
  | Horizontal
  | Vertical;

let make ::initiallyOpenTab=0 ::mode=Vertical ::tabs ::color="#4A90E2" _children => {
  let setTabContainerRef tabContainerRef {ReasonReact.state: state} =>
    ReasonReact.SilentUpdate {...state, tabContainerRef: Js.Null.to_opt tabContainerRef};
  let setActiveTab openTab _ {ReasonReact.state: state} => ReasonReact.Update {...state, openTab};
  let setRect _ {ReasonReact.state: state} =>
    switch state.tabContainerRef {
    | Some containerRef =>
      let children = DomRe.Element.children containerRef;
      let item = DomRe.HtmlCollection.item state.openTab children;
      switch item {
      | Some child =>
        let parentRect = DomRe.Element.getBoundingClientRect containerRef;
        let childRect = DomRe.Element.getBoundingClientRect child;
        Js.log (
          DomRectRe.left childRect - DomRectRe.left parentRect,
          DomRectRe.top childRect - DomRectRe.top parentRect,
          DomRectRe.width childRect,
          DomRectRe.height childRect
        );
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
    | None => ReasonReact.NoUpdate
    };
  {
    ...component,
    initialState: fun () => {
      openTab: initiallyOpenTab,
      activeTabHandleRect: None,
      tabContainerRef: None
    },
    didMount: fun {update} => {
      Bs_webapi.requestAnimationFrame (fun _ => update setRect ());
      ReasonReact.NoUpdate
    },
    didUpdate: fun {oldSelf, newSelf} =>
      if (oldSelf.state.openTab !== newSelf.state.openTab) {
        newSelf.update setRect ()
      },
    render: fun {state, update, enqueue} =>
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
        <div style=(ReactDOMRe.Style.make position::"relative" display::"flex" flexGrow::"0" ())>
          <div
            ref=(enqueue setTabContainerRef)
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
              tabs |>
              Array.mapi (
                fun index (tabTitle, _) =>
                  <TouchableOpacity
                    key=(string_of_int index)
                    style=(
                      ReactDOMRe.Style.make
                        color::(index === state.openTab ? color : "rgba(0, 0, 0, 0.6)")
                        padding::"15px 20px"
                        ()
                    )
                    onPress=(update (setActiveTab index))>
                    tabTitle
                  </TouchableOpacity>
              ) |> ReasonReact.arrayToElement
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
        <div
          style=(ReactDOMRe.Style.make flexGrow::"1" display::"flex" flexDirection::"column" ())>
          {
            let (_activeTab, renderActiveTab) = tabs.(state.openTab);
            renderActiveTab ()
          }
        </div>
      </div>
  }
};
