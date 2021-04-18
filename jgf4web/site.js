
/*
 *  Copyright t lefering
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  These are the four essential freedoms with GNU GPL software:
 *  1: freedom to run the program, for any purpose
 *  2: freedom to study how the program works, and change it to make it do what you wish
 *  3: freedom to redistribute copies to help your Free Software friends
 *  4: freedom to distribute copies of your modified versions to your Free Software friends
 *   ,           ,
 *  /             \
 * ((__-^^-,-^^-__))
 * `-_---'  `---_-'
 *  `--|o`   'o|--'
 *      \  `  /
 *       ): :(
 *       :o_o:
 *        "-"
 */

jQuery(document).ready(function () {

  // Installs error handling.
  jQuery.ajaxSetup({
  error: function(resp, e) {
    if (resp.status == 0){
      } else if (resp.status == 404){
        alert('Requested URL not found.');
      } else if (resp.status == 500){
        alert('Internel Server Error:\n\t' + resp.responseText);
      } else if (e == 'parsererror') {
        alert('Error.\nParsing JSON Request failed.');
      } else if (e == 'timeout') {
        alert('Request timeout.');
      } else {
        alert('Unknown Error.\n' + resp.responseText);
      }
    }
  });

	var svg="";

	var generate_btn = jQuery('#generate_btn');
	var sample_1_btn = jQuery('#sample_1_btn');
	var sample_2_btn = jQuery('#sample_2_btn');
	var sample_3_btn = jQuery('#sample_3_btn');
	var sample_4_btn = jQuery('#sample_4_btn');
	var sample_5_btn = jQuery('#sample_5_btn');
	var sample_6_btn = jQuery('#sample_6_btn');
	var svg_div = jQuery('#graph_svg_div');
	var graph_data_textarea = jQuery('#graph_data');

	function isObject(value) {
		return (value && Object.prototype.toString.call(value) === '[object Object]');
	}

	function forIn(object, callback) {
		Object.keys(object).forEach(function (key) {
			callback(key, object[key]);
		});
	}

	function InsertGraphText(text) {
		graph_data_textarea.val(text);
	}

	function UpdateGraph() {
		var data = graph_data_textarea.val();

		try {
			parsed = JSON.parse(data);
		}
		catch (err) {
			alert("syntax error in json jgf input data");
			return false;
		}


		if (!isObject(parsed.graph)) {
			alert("no \"graph\": {} statement in json jgf input data");
			return false;
		}

		// assume this is a correct jgf file now.

		if (!isObject(parsed.graph.nodes)) {
			alert("no nodes in json jgf input data");
			return false;
		}

		var graph = new dagreD3.graphlib.Graph().setGraph({});

		graph.setGraph({
			nodesep: 15, // 25
			ranksep: 25, // 82
			rankdir: "TB", // or LR
			marginx: 10, // 20
			marginy: 10 // 20
		});

		forIn(parsed.graph.nodes, function (key, value) {
			if(value.label) {
				graph.setNode(key, {label:value.label});
			} else {
				// no label specified, use key as label.
				graph.setNode(key, {label:key});
			}
		});

		forIn(parsed.graph.edges, function (key, value) {
			graph.setEdge(value.source, value.target, {
				curve: d3.curveBasis,
				minlen: 2
			});
		});

		var render = new dagreD3.render();

		// remove old svg drawing if any
		d3.selectAll("g > *").remove();

		svg = d3.select("svg"),
			inner = svg.append("g");

		// Run the renderer. This is what draws the final graph.
		render(inner, graph);

		// Center the graph or left-most min. value 1
		var xCenterOffset = 40; // or center: (svg.attr("width") - graph.graph().width) / 2;
		inner.attr("transform", "translate(" + xCenterOffset + ", 20)");
		svg.attr("height", graph.graph().height + 80); // +40
		svg.attr("width", graph.graph().width + 80); // +40
	}

	// Startup function: call UpdateGraph
	jQuery(function() {
		// The buttons are disabled, enable them now that this script has loaded.
		generate_btn.removeAttr("disabled")
			.text("Generate Graph layout");
		sample_1_btn.removeAttr("disabled");
		sample_2_btn.removeAttr("disabled");
		sample_3_btn.removeAttr("disabled");
		sample_4_btn.removeAttr("disabled");
		sample_5_btn.removeAttr("disabled");
		sample_6_btn.removeAttr("disabled");
	});

	// Bind actions to form buttons.
	generate_btn.click(UpdateGraph);

	sample_1_btn.click(function(){
		InsertGraphText(jQuery("#sample1_text").html().trim());
	});

	sample_2_btn.click(function(){
		InsertGraphText(jQuery("#sample2_text").html().trim());
	});

	sample_3_btn.click(function(){
		InsertGraphText(jQuery("#sample3_text").html().trim());
	});

	sample_4_btn.click(function(){
		InsertGraphText(jQuery("#sample4_text").html().trim());
	});

	sample_5_btn.click(function(){
		InsertGraphText(jQuery("#sample5_text").html().trim());
	});

	sample_6_btn.click(function(){
		InsertGraphText(jQuery("#sample6_text").html().trim());
	});


});

// end.

