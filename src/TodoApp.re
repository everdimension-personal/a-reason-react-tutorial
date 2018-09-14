type action =
  | AddItem
  | ToggleItem(int);

type state = {items: list(ItemData.item)};

type counter = {mutable value: int};
let counter = {value: 0};

let createNewItem = (): ItemData.item => {
  /* record.value = record.value + 1; */
  counter.value = counter.value + 1;
  {
    id: counter.value,
    title: "new item " ++ string_of_int(counter.value),
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
    | ToggleItem(id) =>
      ReasonReact.Update({
        items:
          items
          |> List.map((item: ItemData.item) =>
               item.id === id ? {...item, completed: !item.completed} : item
             ),
      })
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
          if (itemsAmount === 0) {
            ReasonReact.stringToElement("Nothing");
          } else {
            items
            |> List.map((item: ItemData.item) =>
                 <TodoItem
                   key={string_of_int(item.id)}
                   onToggle={() => self.send(ToggleItem(item.id))}
                   item
                 />
               )
            |> Array.of_list
            |> ReasonReact.arrayToElement;
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
