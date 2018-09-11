type item = {
  title: string,
  completed: bool,
};

type action =
  | AddItem;

type state = {items: list(item)};

type counterRecord = {mutable value: int};
let counterRecord = {value: 0};

let createNewItem = () => {
  /* record.value = record.value + 1; */
  counterRecord.value = counterRecord.value + 1;
  {
    title: "new item" ++ string_of_int(counterRecord.value),
    completed: false,
  };
};

let component = ReasonReact.reducerComponent("TodoApp");

let make = _children => {
  ...component,
  initialState: () => {items: []},
  reducer: (action, {items}) =>
    switch (action) {
    | AddItem => ReasonReact.Update({items: [createNewItem(), ...items]})
    },
  render: self => {
    let {items} = self.state;
    let itemsAmount = List.length(items);
    <div className="app">
      <div className="title">
        {ReasonReact.stringToElement("What to do")}
        <button onClick={_evt => self.send(AddItem)}>
          {ReasonReact.stringToElement("Add something")}
        </button>
      </div>
      <div className="items">
        {
          switch (itemsAmount) {
          | 0 => ReasonReact.stringToElement("Nothing")
          | _ =>
            ReasonReact.arrayToElement(
              Array.of_list(List.map(_item => <TodoItem />, items)),
            )
          }
        }
      </div>
      <div className="footer">
        {
          ReasonReact.stringToElement(
            string_of_int(itemsAmount)
            ++ (itemsAmount == 1 ? " item" : " items"),
          )
        }
      </div>
    </div>;
  },
};
