module type FixedCollectionViewRowType = {let name: string; type t;};

type column 't = {
  headerLabel: string,
  style: option ReactDOMRe.Style.t,
  renderHeader: column 't => ReasonReact.reactElement,
  renderCell: 't => ReasonReact.reactElement
};

module Make (FixedCollectionViewRow: FixedCollectionViewRowType) => {
  type t = FixedCollectionViewRow.t;
  type state = {
    containerHeight: option int,
    scrollTop: int,
    containerRef: option Dom.element
  };
  let component =
    ReasonReact.statefulComponent ("FixedCollectionView[" ^ FixedCollectionViewRow.name ^ "]");
  let make
      data::(data: array t)
      ::onEndReached=?
      ::scrollOffset
      ::rowHeight
      ::headerHeight
      columns::(columns: list (column t))
      _children => {
    let setContainerRef containerRef state _self =>
      switch (Js.Null.to_opt containerRef) {
      | Some containerRef => ReasonReact.SilentUpdate {...state, containerRef: Some containerRef}
      | None => ReasonReact.NoUpdate
      };
    let measureContainer () state _self =>
      switch state.containerRef {
      | Some container =>
        ReasonReact.Update {
          ...state,
          containerHeight: Some (DomRe.Element.clientHeight container - headerHeight)
        }
      | _ => ReasonReact.NoUpdate
      };
    let measureContainerAtNextFrame _state self =>
      Bs_webapi.requestAnimationFrame (
        fun _ => {
          self.ReasonReact.update measureContainer ();
          ()
        }
      );
    let setScrollTop event state _self => {
      switch onEndReached {
      | Some onEndReached =>
        if (
          Array.length data * rowHeight - (
            DomRe.Element.scrollTop (ReactEventRe.Synthetic.target event) +
            DomRe.Element.clientHeight (ReactEventRe.Synthetic.target event)
          ) <= scrollOffset
        ) {
          onEndReached ()
        }
      | None => ()
      };
      ReasonReact.Update {
        ...state,
        scrollTop: DomRe.Element.scrollTop (ReactEventRe.Synthetic.target event)
      }
    };
    let renderRow startIndex index (rowData: t) =>
      <div
        key=(string_of_int (index + startIndex))
        style=(
          ReactDOMRe.Style.make
            height::(string_of_int rowHeight ^ "px")
            position::"absolute"
            left::"0px"
            right::"0px"
            top::(string_of_int ((index + startIndex) * rowHeight) ^ "px")
            boxShadow::"0 1px rgba(0, 0, 0, 0.1)"
            display::"flex"
            flexDirection::"row"
            alignItems::"center"
            ()
        )>
        (
          columns |>
          List.mapi (
            fun index column =>
              <div key=(string_of_int index) style=?column.style>
                (column.renderCell rowData)
              </div>
          ) |> Array.of_list |> ReasonReact.arrayToElement
        )
      </div>;
    let renderHeader () =>
      <div
        style=(
          ReactDOMRe.Style.make
            display::"flex"
            flexDirection::"row"
            alignItems::"center"
            height::(string_of_int headerHeight ^ "px")
            ()
        )>
        (
          columns |>
          List.mapi (
            fun index column =>
              <div key=(string_of_int index) style=?column.style>
                (column.renderHeader column)
              </div>
          ) |> Array.of_list |> ReasonReact.arrayToElement
        )
      </div>;
    {
      ...component,
      initialState: fun () => {containerHeight: None, scrollTop: 0, containerRef: None},
      didMount: fun state self => {
        measureContainerAtNextFrame state self;
        ReasonReact.NoUpdate
      },
      render: fun state self =>
        <div
          style=(ReactDOMRe.Style.make flexGrow::"1" width::"100%" ())
          ref=(self.update setContainerRef)>
          (renderHeader ())
          <div
            style=(
              ReactDOMRe.Style.make
                flexGrow::"1"
                overflow::"auto"
                width::"100%"
                height::(
                  switch state.containerHeight {
                  | None => "auto"
                  | Some containerHeight => string_of_int containerHeight ^ "px"
                  }
                )
                ()
            )
            onScroll=(self.update setScrollTop)>
            (
              switch state.containerHeight {
              | None => ReactRe.nullElement
              | Some containerHeight =>
                <div
                  style=(
                    ReactDOMRe.Style.make
                      height::(string_of_int (Array.length data * rowHeight) ^ "px")
                      position::"relative"
                      ()
                  )>
                  {
                    let startIndex = max ((state.scrollTop - scrollOffset) / rowHeight) 0;
                    let renderableCount =
                      min ((containerHeight + scrollOffset * 2) / rowHeight) (Array.length data);
                    Array.sub data startIndex renderableCount |> Array.mapi (renderRow startIndex) |> ReactRe.arrayToElement
                  }
                </div>
              }
            )
          </div>
        </div>
    }
  };
};
