type user = {
  username: string,
  avatar: string
};

module User = {
  let name = "User";
  type t = user;
};

module UserFixedCollectionView = FixedCollectionView.Make User;

let renderUsername rowData => <div> (ReasonReact.stringToElement rowData.username) </div>;

let renderHeader (row: FixedCollectionView.column 'a) =>
  <div style=(ReactDOMRe.Style.make fontSize::"12px" textTransform::"uppercase" ())>
    (ReasonReact.stringToElement row.headerLabel)
  </div>;

let renderGoToProfile _row =>
  <div> <a href="#"> (ReasonReact.stringToElement "View more") </a> </div>;

let renderAvatar rowData =>
  <div>
    <Image width=40 height=40 source=rowData.avatar resizeMode=Contain backgroundColor="#eee" />
  </div>;

let rec renderDemo loading data => {
  let appendData () => {
    renderDemo true data;
    ignore (
      Js.Global.setTimeout
        (
          fun () =>
            renderDemo
              false
              (
                Array.append
                  data
                  (
                    Array.mapi
                      (
                        fun index _item => {
                          username: "username " ^ string_of_int (index + Array.length data),
                          avatar: "https://fakeimg.pl/40x40/"
                        }
                      )
                      (Array.make 50 "")
                  )
              )
        )
        1000
    )
  };
  ReactDOMRe.renderToElementWithId
    <div
      style=(
        ReactDOMRe.Style.make
          backgroundColor::"#fff"
          borderRadius::"2px"
          width::"100%"
          flexGrow::"1"
          display::"flex"
          boxShadow::"0 2px 4px rgba(0, 0, 0, 0.16)"
          ()
      )>
      <UserFixedCollectionView
        data
        scrollOffset=200
        onEndReached=appendData
        headerHeight=30
        rowHeight=60
        footerHeight=(loading ? 200 : 0)
        renderFooter=(
          fun () =>
            loading ?
              <ActivityIndicator size=24.0 color=(200, 200, 200) /> : ReasonReact.nullElement
        )
        columns=[
          {
            headerLabel: "Avatar",
            style: Some (ReactDOMRe.Style.make padding::"0 10px" ()),
            renderHeader,
            renderCell: renderAvatar
          },
          {
            headerLabel: "Name",
            style: Some (ReactDOMRe.Style.make flexGrow::"1" ()),
            renderHeader,
            renderCell: renderUsername
          },
          {
            headerLabel: "ViewMore",
            style: Some (ReactDOMRe.Style.make padding::"0 10px" ()),
            renderHeader: fun _ => ReasonReact.nullElement,
            renderCell: renderGoToProfile
          }
        ]
      />
    </div>
    "root"
};

renderDemo
  false
  (
    Array.mapi
      (
        fun index _item => {
          username: "username " ^ string_of_int index,
          avatar: "https://fakeimg.pl/40x40/"
        }
      )
      (Array.make 50 "")
  );
